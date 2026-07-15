#include "ActorComponents/FlockingComponent.h"
#include "Actors/BoidFlock.h"

#include "Components/SphereComponent.h" 

#include "Defines/PericulumLog.h"

UFlockingComponent::UFlockingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	OverlappingSphereComponent = nullptr;
}

void UFlockingComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentSpeed = FMath::RandRange(FlockSettings.MinSpeed, FlockSettings.MaxSpeed);
	GetOwner()->SetActorRotation(FMath::VRand().Rotation());
	Velocity = GetOwner()->GetActorForwardVector() * CurrentSpeed;
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

		FVector Cohesion = CalculateCohesion(Neighbors) * FlockSettings.CohesionWeight;
		FVector Separation = CalculateSeparation(Neighbors) * FlockSettings.SeparationWeight;
		FVector Alignment = CalculateAlignment(Neighbors) * FlockSettings.AlignmentWeight;
		FVector SteeringForceBoid = CalculateSteeringForce_Boid(Cohesion, Separation, Alignment) * DeltaTime;
		Velocity += SteeringForceBoid;


		FVector Wander = CalculateWander();
		FVector FlockCenter = CalculateFlockCenterAttraction();
		FVector FlockAttraction = CalculateFlockAttractionPoint();
		FVector SteeringForceTuning = CalculateSteeringForce_Tuning(Wander, FlockCenter, FlockAttraction) * DeltaTime;
		Velocity += SteeringForceTuning;
		
		Velocity = Velocity.GetClampedToMaxSize(FlockSettings.MaxSpeed);


		CalculateVelocity(Velocity);
	}
	GetOwner()->AddActorWorldOffset(Velocity * DeltaTime);

	if (!Velocity.IsNearlyZero())
	{
		const FRotator DesiredRotation = Velocity.Rotation();
		const FRotator Smoothed = FMath::RInterpTo(GetOwner()->GetActorRotation(), DesiredRotation, DeltaTime, FlockSettings.TurnSpeed);
		GetOwner()->SetActorRotation(Smoothed);
	}
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
		if (Distance > 0.0f && Distance > FlockSettings.CohesionRadius)
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
	return DesiredDirection * FlockSettings.MaxSpeed - Velocity;
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

		if (Distance > 0.0f && Distance < FlockSettings.SeparationRadius)
		{
			// Weight by inverse distance - closer boids have more influence
			float Strength = (FlockSettings.SeparationRadius / Distance);
			Force += ToNeighbor.GetSafeNormal() * Strength;
			Count++;
		}
	}

	if (Count > 0)
	{
		Force /= Count;
		Force = Force.GetSafeNormal() * FlockSettings.MaxSpeed - Velocity;
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
		if (Distance > 0.0f && Distance > FlockSettings.AlignmentRadius)
		{
			continue; // Skip neighbors that are too far away
		}

		if (UFlockingComponent* NeighborFlocking = Neighbor->FindComponentByClass<UFlockingComponent>())
		{
			AverageVelocity += NeighborFlocking->Velocity;
			Count++;
		}
	}

	if (Count == 0)
	{
		return FVector::ZeroVector;
	}

	AverageVelocity /= Count;
	return AverageVelocity.GetSafeNormal() * FlockSettings.MaxSpeed - Velocity;
}
FVector UFlockingComponent::CalculateSteeringForce_Boid(FVector Cohesion, FVector Separation, FVector Alignment)
{
	FVector SteeringForce = Cohesion + Separation + Alignment;
	SteeringForce = SteeringForce.GetClampedToMaxSize(FlockSettings.MaxForce);
	return SteeringForce;
}

FVector UFlockingComponent::CalculateWander()
{
	FVector WanderMax = FMath::VRand() * FlockSettings.MaxWanderStrength;
	FVector WanderMin = FMath::VRand() * FlockSettings.MinWanderStrength;
	
	FVector WanderForce = (WanderMax + WanderMin) / 2.0f;
	return WanderForce;
}
FVector UFlockingComponent::CalculateFlockCenterAttraction()
{
	if (!FlockManager)
	{
		return FVector::ZeroVector;
	}

	FVector FlockCenter = FlockSettings.FlockCenter;
	FVector AttractionForce = (FlockCenter - GetOwner()->GetActorLocation()).GetSafeNormal() * FlockSettings.FlockCenterStrength;
	return AttractionForce;
}
FVector UFlockingComponent::CalculateFlockAttractionPoint()
{
	if (!FlockManager)
	{
		return FVector::ZeroVector;
	}

	FVector AttractionPoint = FlockSettings.FlockAttractionPoint;
	FVector AttractionForce = (AttractionPoint - GetOwner()->GetActorLocation()).GetSafeNormal() * FlockSettings.FlockAttractionPointStrength;
	return AttractionForce;
}
FVector UFlockingComponent::CalculateSteeringForce_Tuning(FVector Wander, FVector FlockCenter, FVector FlockAttraction)
{
	FVector SteeringForce = Wander + FlockCenter + FlockAttraction;
	SteeringForce = SteeringForce.GetClampedToMaxSize(FlockSettings.MaxForce);
	return SteeringForce;
}

void UFlockingComponent::CalculateVelocity(FVector CurrentVelocity)
{
	const float Speed = CurrentVelocity.Size();
	if (Speed > FlockSettings.MaxSpeed)
	{
		Velocity = CurrentVelocity.GetSafeNormal() * FlockSettings.MaxSpeed;
	}
	else if (Speed < FlockSettings.MinSpeed && Speed > 0.0f)
	{
		Velocity = CurrentVelocity.GetSafeNormal() * FlockSettings.MinSpeed;
	}
}

void UFlockingComponent::UpdateFlockSettings(const FFlockSettings& NewSettings)
{
	FlockSettings.CohesionWeight = NewSettings.CohesionWeight;
	FlockSettings.CohesionRadius = NewSettings.CohesionRadius;

	FlockSettings.SeparationWeight = NewSettings.SeparationWeight;
	FlockSettings.SeparationRadius = NewSettings.SeparationRadius;

	FlockSettings.AlignmentWeight = NewSettings.AlignmentWeight;
	FlockSettings.AlignmentRadius = NewSettings.AlignmentRadius;

	float Radius = FlockSettings.SeparationRadius + FlockSettings.AlignmentRadius + FlockSettings.CohesionRadius;
	Radius /= 3.f; // Average the radius for visualization
	if (OverlappingSphereComponent)
	{
		OverlappingSphereComponent->SetSphereRadius(Radius);
	}

	FlockSettings.MaxSpeed = NewSettings.MaxSpeed;
	FlockSettings.MinSpeed = NewSettings.MinSpeed;

	FlockSettings.MaxWanderStrength = NewSettings.MaxWanderStrength;
	FlockSettings.MinWanderStrength = NewSettings.MinWanderStrength;

	FlockSettings.MaxForce = NewSettings.MaxForce;
	FlockSettings.TurnSpeed = NewSettings.TurnSpeed;

	FlockSettings.FlockCenter = NewSettings.FlockCenter;
	FlockSettings.FlockCenterStrength = NewSettings.FlockCenterStrength;

	FlockSettings.FlockAttractionPoint = NewSettings.FlockAttractionPoint;
	FlockSettings.FlockAttractionPointStrength = NewSettings.FlockAttractionPointStrength;

	FlockSettings.bDrawDebugRadiusAverage = NewSettings.bDrawDebugRadiusAverage;
	FlockSettings.bDrawDebugSightLine = NewSettings.bDrawDebugSightLine;
}

void UFlockingComponent::DrawOverlapComponentBounds()
{
	if (FlockSettings.bDrawDebugRadiusAverage) {

		if (OverlappingSphereComponent)
		{
			float Radius = FlockSettings.SeparationRadius + FlockSettings.AlignmentRadius + FlockSettings.CohesionRadius;
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
		float Radius = FlockSettings.SeparationRadius + FlockSettings.AlignmentRadius + FlockSettings.CohesionRadius;

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
