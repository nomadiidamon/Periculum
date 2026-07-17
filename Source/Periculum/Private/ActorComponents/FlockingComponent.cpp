#include "ActorComponents/FlockingComponent.h"
#include "Actors/BoidFlock.h"

#include "Components/SphereComponent.h" 

#include "DataAssets/BoidFlockSettings.h"

#include "Defines/PericulumLog.h"

UFlockingComponent::UFlockingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	OverlappingSphereComponent = nullptr;
}

void UFlockingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (FlockManager) {
		BoidSettings.CurrentSpeed = FMath::RandRange(FlockManager->FlockSettings->MinSpeed, FlockManager->FlockSettings->MaxSpeed);
	}
	else {
		BoidSettings.CurrentSpeed = FMath::RandRange(15.0f, 75.0f);
	}
	GetOwner()->SetActorRotation(FMath::VRand().Rotation());
	BoidSettings.Velocity = GetOwner()->GetActorForwardVector() * BoidSettings.CurrentSpeed;
}

#define FLOCKING_DEBUG 0
void UFlockingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FlockManager)
	{

#if FLOCKING_DEBUG == 1
		TArray<AActor*> Neighbors = FlockManager->GetNeighboringBoids(GetOwner(), FlockSettings.CohesionRadius);
#elif FLOCKING_DEBUG == 0
		TArray<AActor*> Neighbors;
		TArray<AActor*> CurrentOverlappingActors = OverlappingActors;

		for (AActor* Actor : CurrentOverlappingActors)
		{
			if (Actor != GetOwner() && Actor->FindComponentByClass<UFlockingComponent>())
			{
				Neighbors.Add(Actor);
			}
		}
#endif

		FVector Cohesion = CalculateCohesion(Neighbors) * FlockManager->FlockSettings->CohesionWeight;
		FVector Separation = CalculateSeparation(Neighbors) * FlockManager->FlockSettings->SeparationWeight;
		FVector Alignment = CalculateAlignment(Neighbors) * FlockManager->FlockSettings->AlignmentWeight;
		FVector SteeringForceBoid = CalculateSteeringForce_Boid(Cohesion, Separation, Alignment) * DeltaTime;
		BoidSettings.Velocity += SteeringForceBoid;


		FVector Wander = CalculateWander();
		FVector FlockCenter = CalculateFlockCenterAttraction();
		FVector FlockAttraction = CalculateFlockAttractionPoint();
		FVector SteeringForceTuning = CalculateSteeringForce_Tuning(Wander, FlockCenter, FlockAttraction) * DeltaTime;
		BoidSettings.Velocity += SteeringForceTuning;

		BoidSettings.Velocity = BoidSettings.Velocity.GetClampedToMaxSize(FlockManager->FlockSettings->MaxSpeed);


		CalculateVelocity(BoidSettings.Velocity);
	}
	GetOwner()->AddActorWorldOffset(BoidSettings.Velocity * DeltaTime);

	if (!BoidSettings.Velocity.IsNearlyZero())
	{
		const FRotator DesiredRotation = BoidSettings.Velocity.Rotation();
		const FRotator Smoothed = FMath::RInterpTo(GetOwner()->GetActorRotation(), DesiredRotation, DeltaTime, FlockManager->FlockSettings->TurnSpeed);
		GetOwner()->SetActorRotation(Smoothed);
	}
}

void UFlockingComponent::AvoidObstacle(FVector ObstacleLocation, FVector ObstacleNormal, FVector CurrentVelocity)
{
	FVector BoidVelocity = CurrentVelocity.GetSafeNormal();
	FVector BoidLocation = GetOwner()->GetActorLocation();

	FVector ToObstacle = ObstacleLocation - BoidLocation;
	FVector AvoidanceDirection = FVector::CrossProduct(ToObstacle, ObstacleNormal).GetSafeNormal();

	FVector DesiredVelocity = AvoidanceDirection * FlockManager->FlockSettings->MaxSpeed;

	FVector SteeringForce = DesiredVelocity - BoidVelocity;

	BoidSettings.Velocity += SteeringForce.GetClampedToMaxSize(FlockManager->FlockSettings->MaxForce);
}

FVector UFlockingComponent::CalculateCohesion(TArray<AActor*> Neighbors)
{
	if (Neighbors.Num() == 0)
	{
		return FVector::ZeroVector;
	}

	FVector Center = FVector::ZeroVector;
	int32 CohesionCount = 0;

	for (AActor* Neighbor : Neighbors)
	{
		FVector ToNeighbor = Neighbor->GetActorLocation() - GetOwner()->GetActorLocation();
		float Distance = ToNeighbor.Size();
		if (Distance > 0.0f && Distance > BoidSettings.CohesionRadius)
		{
			continue; // Skip neighbors that are too far away
		}

		CohesionCount++;
		Center += Neighbor->GetActorLocation();
	}

	if (CohesionCount == 0)
	{
		return FVector::ZeroVector;
	}

	Center /= CohesionCount;
	FVector DesiredDirection = (Center - GetOwner()->GetActorLocation()).GetSafeNormal();
	return DesiredDirection * FlockManager->FlockSettings->MaxSpeed - BoidSettings.Velocity;
}

FVector UFlockingComponent::CalculateSeparation(TArray<AActor*> Neighbors)
{
	if (Neighbors.Num() == 0)
	{
		return FVector::ZeroVector;
	}

	FVector Force = FVector::ZeroVector;
	int32 Count = 0;

	for (AActor* Neighbor : Neighbors)
	{
		FVector ToNeighbor = GetOwner()->GetActorLocation() - Neighbor->GetActorLocation();
		float Distance = ToNeighbor.Size();

		if (Distance > 0.0f && Distance < BoidSettings.SeparationRadius)
		{
			// Weight by inverse distance - closer boids have more influence
			float Strength = (BoidSettings.SeparationRadius / Distance);
			Force += ToNeighbor.GetSafeNormal() * Strength;
			Count++;
		}
	}

	if (Count > 0)
	{
		Force /= Count;
		Force = Force.GetSafeNormal() * FlockManager->FlockSettings->MaxSpeed - BoidSettings.Velocity;
	}

	return Force;
}

FVector UFlockingComponent::CalculateAlignment(TArray<AActor*> Neighbors)
{
	if (Neighbors.Num() == 0)
	{
		return FVector::ZeroVector;
	}

	FVector AverageVelocity = FVector::ZeroVector;
	int32 Count = 0;

	for (AActor* Neighbor : Neighbors)
	{
		FVector ToNeighbor = Neighbor->GetActorLocation() - GetOwner()->GetActorLocation();
		float Distance = ToNeighbor.Size();
		if (Distance > 0.0f && Distance > BoidSettings.AlignmentRadius)
		{
			continue; // Skip neighbors that are too far away
		}

		if (UFlockingComponent* NeighborFlocking = Neighbor->FindComponentByClass<UFlockingComponent>())
		{
			AverageVelocity += NeighborFlocking->BoidSettings.Velocity;
			Count++;
		}
	}

	if (Count == 0)
	{
		return FVector::ZeroVector;
	}

	AverageVelocity /= Count;
	return AverageVelocity.GetSafeNormal() * FlockManager->FlockSettings->MaxSpeed - BoidSettings.Velocity;
}

FVector UFlockingComponent::CalculateSteeringForce_Boid(FVector Cohesion, FVector Separation, FVector Alignment)
{
	FVector SteeringForce = Cohesion + Separation + Alignment;
	SteeringForce = SteeringForce.GetClampedToMaxSize(FlockManager->FlockSettings->MaxForce);
	return SteeringForce;
}

FVector UFlockingComponent::CalculateWander()
{
	FVector WanderMax = FMath::VRand() * FlockManager->FlockSettings->MaxWanderStrength;
	FVector WanderMin = FMath::VRand() * FlockManager->FlockSettings->MinWanderStrength;

	FVector WanderForce = (WanderMax + WanderMin) / 2.0f;
	return WanderForce;
}

FVector UFlockingComponent::CalculateFlockCenterAttraction()
{
	if (!FlockManager)
	{
		return FVector::ZeroVector;
	}

	FVector FlockCenter = FlockManager->FlockSettings->FlockCenter;
	BoidSettings.FlockCenter = FlockCenter;
	FVector AttractionForce = (FlockCenter - GetOwner()->GetActorLocation()).GetSafeNormal() * FlockManager->FlockSettings->FlockCenterStrength;
	return AttractionForce;
}

FVector UFlockingComponent::CalculateFlockAttractionPoint()
{
	if (!FlockManager)
	{
		return FVector::ZeroVector;
	}

	FVector AttractionPoint = FlockManager->FlockSettings->FlockAttractionPoint;
	BoidSettings.AttractionPoint = AttractionPoint;
	FVector AttractionForce = (AttractionPoint - GetOwner()->GetActorLocation()).GetSafeNormal() * FlockManager->FlockSettings->FlockAttractionPointStrength;
	return AttractionForce;
}

FVector UFlockingComponent::CalculateSteeringForce_Tuning(FVector Wander, FVector FlockCenter, FVector FlockAttraction)
{
	FVector SteeringForce = Wander + FlockCenter + FlockAttraction;
	SteeringForce = SteeringForce.GetClampedToMaxSize(FlockManager->FlockSettings->MaxForce);
	return SteeringForce;
}

void UFlockingComponent::CalculateVelocity(FVector CurrentVelocity)
{
	const float Speed = CurrentVelocity.Size();
	if (Speed > FlockManager->FlockSettings->MaxSpeed)
	{
		BoidSettings.Velocity = CurrentVelocity.GetSafeNormal() * FlockManager->FlockSettings->MaxSpeed;
	}
	else if (Speed < FlockManager->FlockSettings->MinSpeed && Speed > 0.0f)
	{
		BoidSettings.Velocity = CurrentVelocity.GetSafeNormal() * FlockManager->FlockSettings->MinSpeed;
	}
}

void UFlockingComponent::DrawOverlapComponentBounds()
{
	if (FlockManager) {

		if (OverlappingSphereComponent)
		{
			float Radius = BoidSettings.SeparationRadius + BoidSettings.AlignmentRadius + BoidSettings.CohesionRadius;
			Radius /= 3.f; // Average the radius for visualization

			DrawDebugSphere(
				GetWorld(),
				OverlappingSphereComponent->GetComponentLocation(),
				Radius,
				12,
				FColor::Red,
				false,
				-1.f,
				0,
				2.f
			);
		}
	}
}

void UFlockingComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is valid and not the owner of this component
	if (OtherActor && OtherActor != GetOwner())
	{
		float distance = FVector::Dist(GetOwner()->GetActorLocation(), OtherActor->GetActorLocation());
		float Radius = BoidSettings.SeparationRadius + BoidSettings.AlignmentRadius + BoidSettings.CohesionRadius;

		if (distance <= Radius)
		{
			// Add the overlapping actor to the array
			OverlappingActors.AddUnique(OtherActor);
		}
		else
		{
			// Remove the overlapping actor from the array if it's too far away
			OverlappingActors.Remove(OtherActor);
		}
	}
}

void UFlockingComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the overlapping actor is valid and not the owner of this component
	if (OtherActor && OtherActor != GetOwner())
	{
		// Remove the overlapping actor from the array
		OverlappingActors.Remove(OtherActor);
	}
}
