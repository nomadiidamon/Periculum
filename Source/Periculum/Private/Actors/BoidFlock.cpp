#include "Actors/BoidFlock.h"
#include "Actors/Boid.h"

#include "Components/FlockingComponent.h"
#include "Components/BoxSpawnerComponent.h"
#include "Components/CapsuleSpawnerComponent.h"
#include "Components/SphereSpawnerComponent.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "Defines/PericulumLog.h"

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
}

void ABoidFlock::BeginPlay()
{
	Super::BeginPlay();

	ActorToSpawn = BoidClass;

	if (ActorToSpawn == nullptr)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "ActorToSpawn is not set in BoidFlock. Please set it to a valid Boid class to enable spawning.");
	}

	LastFlockSettings = FlockSettings;

	if (!OnSpawnableActorSpawned.IsAlreadyBound(this, &ABoidFlock::RegisterBoid))
	{
		OnSpawnableActorSpawned.AddDynamic(this, &ABoidFlock::RegisterBoid);
	}
	if (!OnFlockSettingsChanged.IsAlreadyBound(this, &ABoidFlock::UpdateBoidSettings))
	{
		OnFlockSettingsChanged.AddDynamic(this, &ABoidFlock::UpdateBoidSettings);
	}
}

void ABoidFlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LastFlockSettings != FlockSettings)
	{
		LastFlockSettings = FlockSettings;
		if (OnFlockSettingsChanged.IsBound())
		{
			OnFlockSettingsChanged.Broadcast(FlockSettings);
		}
	}

	FVector AverageLocation = FVector::ZeroVector;

	for (AActor* Boid : Boids)
	{
		if (Boid)
		{
			AverageLocation += Boid->GetActorLocation();
		}
	}

	if (Boids.Num() > 0)
	{
		AverageLocation /= Boids.Num();
	}

	FlockSettings.FlockCenter = AverageLocation;
}


void ABoidFlock::RegisterBoid(AActor* Boid)
{
	Boids.AddUnique(Boid);
	if (ABoid* BoidActor = Cast<ABoid>(Boid))
	{
		if (UFlockingComponent* FlockingComp = BoidActor->GetFlockingComponent())
		{
			FlockingComp->SetFlockManager(this);
			FlockingComp->UpdateFlockSettings(FlockSettings);
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

	for (auto OtherBoid : Boids)
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
			BoidActor->bDrawDebugRadius = NewSettings.bDrawDebugRadiusAverage;
			BoidActor->bDrawDebugSightLine = NewSettings.bDrawDebugSightLine;
			if (UFlockingComponent* FlockingComp = BoidActor->GetFlockingComponent())
			{
				FlockingComp->UpdateFlockSettings(NewSettings);
			}
		}
	}
}

