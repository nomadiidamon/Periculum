#include "Code/Components/FlockingComponent.h"
#include "Code/Actors/BoidFlock.h"

#include "Components/SphereComponent.h" 

#include "Code/Utility/PericulumLog.h"

UFlockingComponent::UFlockingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	OverlappingComponent = nullptr;
}


void UFlockingComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentSpeed = FMath::RandRange(FlockSettings.MinSpeed, FlockSettings.MaxSpeed);
	GetOwner()->SetActorRotation(FMath::VRand().Rotation());
	Velocity = GetOwner()->GetActorForwardVector() * CurrentSpeed;
}


void UFlockingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!FlockManager)
	{
		return;
	}

	TArray<AActor*> Neighbors;
	TArray<AActor*> CurrentOverlappingActors = OverlappingActors;

	for (AActor* Actor : CurrentOverlappingActors)
	{
		if (Actor != GetOwner() && Actor->FindComponentByClass<UFlockingComponent>())
		{
			Neighbors.Add(Actor);
		}
	}

	FVector Cohesion = CalculateCohesion(Neighbors) * FlockSettings.CohesionWeight;
	FVector Separation = CalculateSeparation(Neighbors) * FlockSettings.SeparationWeight;
	FVector Alignment = CalculateAlignment(Neighbors) * FlockSettings.AlignmentWeight;

	// Apply steering forces with proper acceleration
	FVector SteeringForce = Separation + Alignment + Cohesion;
	Velocity += SteeringForce * DeltaTime;

	// Clamp velocity to min/max speed range
	float Speed = Velocity.Size();
	if (Speed > FlockSettings.MaxSpeed)
	{
		Velocity = Velocity.GetSafeNormal() * FlockSettings.MaxSpeed;
	}
	else if (Speed < FlockSettings.MinSpeed && Speed > 0.0f)
	{
		Velocity = Velocity.GetSafeNormal() * FlockSettings.MinSpeed;
	}

	GetOwner()->AddActorWorldOffset(Velocity * DeltaTime);

	// Only rotate if velocity is significant
	if (!Velocity.IsNearlyZero())
	{
		GetOwner()->SetActorRotation(Velocity.Rotation());
	}
}

FVector UFlockingComponent::CalculateCohesion(TArray<AActor*> Neighbors)
{
	if (Neighbors.Num() == 0)
	{
		return FVector::ZeroVector;
	}

	FVector Center = FVector::ZeroVector;
	for (AActor* Neighbor : Neighbors)
	{
		Center += Neighbor->GetActorLocation();
	}

	Center /= Neighbors.Num();
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

		if (Distance > 0.0f && Distance < FlockSettings.SafeRadius)
		{
			// Weight by inverse distance - closer boids have more influence
			Force += ToNeighbor.GetSafeNormal() / Distance;
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

	for (AActor* Neighbor : Neighbors)
	{
		UFlockingComponent* NeighborFlocking = Neighbor->FindComponentByClass<UFlockingComponent>();
		if (NeighborFlocking)
		{
			AverageVelocity += NeighborFlocking->Velocity;
		}
	}

	AverageVelocity /= Neighbors.Num();
	return AverageVelocity.GetSafeNormal() * FlockSettings.MaxSpeed - Velocity;
}

void UFlockingComponent::UpdateFlockSettings(const FFlockSettings& NewSettings)
{
	FlockSettings.SeparationWeight = NewSettings.SeparationWeight;
	FlockSettings.AlignmentWeight = NewSettings.AlignmentWeight;
	if (!FMath::IsNearlyEqual(FlockSettings.SafeRadius, NewSettings.SafeRadius))
	{
		FlockSettings.SafeRadius = NewSettings.SafeRadius;
		if (OverlappingComponent)
		{
			OverlappingComponent->SetSphereRadius(FlockSettings.SafeRadius);
		}
	}
	FlockSettings.MaxSpeed = NewSettings.MaxSpeed;
	FlockSettings.MinSpeed = NewSettings.MinSpeed;
	FlockSettings.bDrawDebug = NewSettings.bDrawDebug;

	//if (!Velocity.IsNearlyZero())
	//{
	//	float Speed = Velocity.Size();
	//	if (Speed > FlockSettings.MaxSpeed)
	//	{
	//		Velocity = Velocity.GetSafeNormal() * FlockSettings.MaxSpeed;
	//	}
	//	else if (Speed < FlockSettings.MinSpeed)
	//	{
	//		Velocity = Velocity.GetSafeNormal() * FlockSettings.MinSpeed;
	//	}
	//}
}

void UFlockingComponent::DrawOverlapComponentBounds()
{
	if (OverlappingComponent)
	{
		DrawDebugSphere(
			GetWorld(),
			OverlappingComponent->GetComponentLocation(),
			OverlappingComponent->GetScaledSphereRadius(),
			12,
			FColor::Red,
			false,
			-1.f,
			0,
			2.f
		);
	}
}

void UFlockingComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is valid and not the owner of this component
	if (OtherActor && OtherActor != GetOwner())
	{
		// Add the overlapping actor to the array
		OverlappingActors.AddUnique(OtherActor);
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
