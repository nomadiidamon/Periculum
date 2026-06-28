#include "Code/Components/FlockingComponent.h"
#include "Code/Actors/BoidFlock.h"
#include "Code/Actors/Boid.h"

#include "Components/SphereComponent.h" 

#include "Code/Utility/PericulumLog.h"

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
		TArray<AActor*> Neighbors = FlockManager->GetNeighboringBoids(GetOwner(), FlockSettings.CollisionDetectionRadius);
#elif FLOCKING_DEBUG == 0
		TArray<AActor*> Neighbors;
		TArray<AActor*> CurrentOverlappingActors = OverlappingActors;

		for (AActor* Actor : CurrentOverlappingActors)
		{
			if (ABoid* boid = Cast<ABoid>(Actor))
			{
				if (boid->HasFlockingComponent())
				{
					Neighbors.Add(Actor);
				}
			}
		}
#endif
		FVector SteeringForce = FVector::ZeroVector;
		SteeringForce += ExecuteBoidBehavior(Neighbors);
		SteeringForce += ExecuteTuningBehavior();
		Velocity = SteeringForce.GetClampedToMaxSize(FlockSettings.MaxSpeed);


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

FVector UFlockingComponent::ExecuteBoidBehavior(TArray<AActor*> Neighbors)
{
	FVector Cohesion = CalculateCohesion(Neighbors) * FlockSettings.CohesionWeight;
	FVector Separation = CalculateSeparation(Neighbors) * FlockSettings.SeparationWeight;
	FVector Alignment = CalculateAlignment(Neighbors) * FlockSettings.AlignmentWeight;
	FVector SteeringForceBoid = CalculateSteeringForce_Boid(Cohesion, Separation, Alignment);
	return SteeringForceBoid;
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
			float Strength = FMath::Square(1.0f - (Distance / FlockSettings.SeparationRadius));
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

		FVector velocity = Neighbor->GetVelocity();
		if (velocity.SizeSquared() > 0.0f)
		{
			AverageVelocity += velocity;
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
	return SteeringForce;
}

FVector UFlockingComponent::ExecuteTuningBehavior()
{
	FVector Wander = CalculateWander();
	FVector FlockCenter = CalculateFlockCenterAttraction();
	FVector FlockAttraction = CalculateFlockAttractionPoint();
	FVector SteeringForceTuning = CalculateSteeringForce_Tuning(Wander, FlockCenter, FlockAttraction);
	return SteeringForceTuning;
}

FVector UFlockingComponent::CalculateWander()
{
	FVector WanderDirection = FMath::VRand().GetSafeNormal();
	WanderVector += WanderDirection * FMath::RandRange(FlockSettings.MinWanderStrength, FlockSettings.MaxWanderStrength);
	WanderVector.Normalize();
	return WanderVector;
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
	return SteeringForce;
}

FVector UFlockingComponent::PredictCollisions(TArray<AActor*> Actors, float DeltaTime)
{
	return FVector();
}

FVector UFlockingComponent::PredictFuturePosition(float DeltaTime)
{
	return FVector();
}

FVector UFlockingComponent::PredictNeighborPosition(ABoid* Neighbor, float DeltaTime)
{
	return FVector();
}

FVector UFlockingComponent::CalculateObstacleDistance(AActor* Obstacle, float DeltaTime)
{
	return FVector();
}

FVector UFlockingComponent::PredictObstacleCollision(AActor* Obstacle, float DeltaTime)
{
	return FVector();
}

FVector UFlockingComponent::AvoidObstaclesCollisions(TArray<AActor*> Obstacles, float DeltaTime)
{
	return FVector();
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

	if (OverlappingSphereComponent)
	{
		OverlappingSphereComponent->SetSphereRadius(FlockSettings.CollisionDetectionRadius);
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
			DrawDebugSphere(
				GetWorld(),
				OverlappingSphereComponent->GetComponentLocation(),
				FlockSettings.CollisionDetectionRadius,
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

		if (distance <= FlockSettings.CollisionDetectionRadius)
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
