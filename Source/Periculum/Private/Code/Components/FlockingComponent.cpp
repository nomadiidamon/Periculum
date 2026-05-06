#include "Code/Components/FlockingComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h" 
#include "Code/Actors/BoidFlock.h"

UFlockingComponent::UFlockingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	//OverlappingComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	//OverlappingComponent->SetSphereRadius(safeRadius);

	//OverlappingComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//OverlappingComponent->SetCollisionProfileName(TEXT("BlockDynamic"));
}


void UFlockingComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentSpeed = FMath::RandRange(MinSpeed, MaxSpeed);
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

	DrawOverlapComponentBounds();

	TArray<AActor*> Neighbors = FlockManager->GetNeighboringBoids(GetOwner(), safeRadius);

	FVector Cohesion = CalculateCohesion(Neighbors) * cohesionWeight;
	FVector Separation = CalculateSeparation(Neighbors) * separationWeight;
	FVector Alignment = CalculateAlignment(Neighbors) * alignmentWeight;

	// Apply steering forces with proper acceleration
	FVector SteeringForce = Separation + Alignment + Cohesion;
	Velocity += SteeringForce * DeltaTime;

	// Clamp velocity to min/max speed range
	float Speed = Velocity.Size();
	if (Speed > MaxSpeed)
	{
		Velocity = Velocity.GetSafeNormal() * MaxSpeed;
	}
	else if (Speed < MinSpeed && Speed > 0.0f)
	{
		Velocity = Velocity.GetSafeNormal() * MinSpeed;
	}

	GetOwner()->AddActorWorldOffset(Velocity * DeltaTime);

	// Only rotate if velocity is significant
	if (!Velocity.IsNearlyZero())
	{
		GetOwner()->SetActorRotation(Velocity.Rotation());
	}
	UpdateFlockSettings(FlockManager->FlockSettings);
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
	return DesiredDirection * MaxSpeed - Velocity;
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

		if (Distance > 0.0f && Distance < safeRadius)
		{
			// Weight by inverse distance - closer boids have more influence
			Force += ToNeighbor.GetSafeNormal() / Distance;
			Count++;
		}
	}

	if (Count > 0)
	{
		Force /= Count;
		Force = Force.GetSafeNormal() * MaxSpeed - Velocity;
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
	return AverageVelocity.GetSafeNormal() * MaxSpeed - Velocity;
}

void UFlockingComponent::UpdateFlockSettings(const FFlockSettings& NewSettings)
{
	cohesionWeight = NewSettings.CohesionWeight;
	separationWeight = NewSettings.SeparationWeight;
	alignmentWeight = NewSettings.AlignmentWeight;
	safeRadius = NewSettings.SafeRadius;
//	OverlappingComponent->SetSphereRadius(safeRadius);
	MaxSpeed = NewSettings.MaxSpeed;
	MinSpeed = NewSettings.MinSpeed;

}

void UFlockingComponent::DrawOverlapComponentBounds()
{
	if (!OverlappingComponent)
	{
		return;
	}

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

