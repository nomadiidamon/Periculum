#include "Code/Actors/BoidFlock.h"
#include "Code/Actors/Boid.h"

#include "Code/Components/FlockingComponent.h"
#include "Code/Components/BoxSpawnerComponent.h"
#include "Components/BoxComponent.h"
#include "Code/Components/CapsuleSpawnerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Code/Components/SphereSpawnerComponent.h"
#include "Components/SphereComponent.h"

#include "Code/Utility/PericulumLog.h"

ABoidFlock::ABoidFlock()
{
	PrimaryActorTick.bCanEverTick = true;

	if (BoidClass == nullptr)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "BoidClass is not set in BoidFlock. Please set it to a valid Boid class to enable spawning.");
	}
	else {
		ActorToSpawn = BoidClass;
	}

	OnSpawnableActorSpawned.AddDynamic(this, &ABoidFlock::RegisterBoid);
}

void ABoidFlock::BeginPlay()
{
	Super::BeginPlay();

	ActorToSpawn = BoidClass;

	if (ActorToSpawn == nullptr)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "ActorToSpawn is not set in BoidFlock. Please set it to a valid Boid class to enable spawning.");
	}
	else {
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ABoidFlock::SpawnBoids, SpawnInterval, true);
	}

	OnFlockSettingsChanged.AddDynamic(this, &ABoidFlock::UpdateBoidSettings);
}

void ABoidFlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LastFlockSettings != FlockSettings)
	{
		LastFlockSettings = FlockSettings;
		UpdateBoidSettings(FlockSettings);
		if (OnFlockSettingsChanged.IsBound())
		{
			OnFlockSettingsChanged.Broadcast(FlockSettings);
		}
	}
}


void ABoidFlock::RegisterBoid(AActor* Boid)
{
	Boids.AddUnique(Boid);

	if (ABoid* BoidActor = Cast<ABoid>(Boid))
	{
		if (UFlockingComponent* FlockingComp = BoidActor->GetFlockingComponent())
		{
			FlockingComp->SetFlockManager(this);

			FlockingComp->cohesionWeight = FlockSettings.CohesionWeight;
			FlockingComp->separationWeight = FlockSettings.SeparationWeight;
			FlockingComp->alignmentWeight = FlockSettings.AlignmentWeight;
			FlockingComp->safeRadius = FlockSettings.SafeRadius;
			FlockingComp->MaxSpeed = FlockSettings.MaxSpeed;
			FlockingComp->MinSpeed = FlockSettings.MinSpeed;

			if (!FlockingComp->Velocity.IsNearlyZero())
			{
				float Speed = FlockingComp->Velocity.Size();
				if (Speed > FlockSettings.MaxSpeed)
				{
					FlockingComp->Velocity = FlockingComp->Velocity.GetSafeNormal() * FlockSettings.MaxSpeed;
				}
				else if (Speed < FlockSettings.MinSpeed)
				{
					FlockingComp->Velocity = FlockingComp->Velocity.GetSafeNormal() * FlockSettings.MinSpeed;
				}
			}
		}
	}
}

void ABoidFlock::SpawnBoids()
{
	SpawnActor();
}

TArray<AActor*> ABoidFlock::GetNeighboringBoids(AActor* Boid, float Radius) const
{
	TArray<AActor*> Neighbors;

	FVector Location = Boid->GetActorLocation();

	for (AActor* OtherBoid : Boids)
	{
		if (OtherBoid == Boid)
		{
			continue; // Skip the current boid
		}

		if (FVector::Dist(Location, OtherBoid->GetActorLocation()) <= Radius)
		{
			Neighbors.Add(OtherBoid);
		}
	}
	return Neighbors;
}

void ABoidFlock::UpdateBoidSettings(const FFlockSettings& NewSettings)
{
	for (AActor* Boid : Boids)
	{
		if (ABoid* BoidActor = Cast<ABoid>(Boid))
		{
			if (UFlockingComponent* FlockingComp = BoidActor->GetFlockingComponent())
			{
				FlockingComp->cohesionWeight = NewSettings.CohesionWeight;
				FlockingComp->separationWeight = NewSettings.SeparationWeight;
				FlockingComp->alignmentWeight = NewSettings.AlignmentWeight;
				FlockingComp->safeRadius = NewSettings.SafeRadius;
				FlockingComp->MaxSpeed = NewSettings.MaxSpeed;
				FlockingComp->MinSpeed = NewSettings.MinSpeed;
				if (!FlockingComp->Velocity.IsNearlyZero())
				{
					float Speed = FlockingComp->Velocity.Size();
					if (Speed > NewSettings.MaxSpeed)
					{
						FlockingComp->Velocity = FlockingComp->Velocity.GetSafeNormal() * NewSettings.MaxSpeed;
					}
					else if (Speed < NewSettings.MinSpeed)
					{
						FlockingComp->Velocity = FlockingComp->Velocity.GetSafeNormal() * NewSettings.MinSpeed;
					}
				}
			}
		}
	}
}
