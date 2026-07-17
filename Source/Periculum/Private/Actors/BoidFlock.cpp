#include "Actors/BoidFlock.h"
#include "Actors/Boid.h"

#include "ActorComponents/FlockingComponent.h"
#include "ActorComponents/MessagingComponent.h"

#include "SceneComponents/BoxSpawnerComponent.h"
#include "SceneComponents/CapsuleSpawnerComponent.h"
#include "SceneComponents/SphereSpawnerComponent.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "DataAssets/BoidFlockSettings.h"

#include "Defines/PericulumLog.h"

#include "GameFramework/Character.h"
#include "EngineUtils.h"

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

	MessagingComponent = CreateDefaultSubobject<UMessagingComponent>(TEXT("MessagingComponent"));
}

void ABoidFlock::BeginPlay()
{
	Super::BeginPlay();

	ActorToSpawn = BoidClass;

	if (!FlockSettings)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "FlockSettings is not set in BoidFlock. Please set it to a valid UBoidFlockSettings instance to enable flocking behavior.");
	}

	if (ActorToSpawn == nullptr)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "ActorToSpawn is not set in BoidFlock. Please set it to a valid Boid class to enable spawning.");
	}

	if (!OnSpawnableActorSpawned.IsAlreadyBound(this, &ABoidFlock::RegisterBoid))
	{
		OnSpawnableActorSpawned.AddDynamic(this, &ABoidFlock::RegisterBoid);
	}

	for (TActorIterator<ACharacter> It(GetWorld()); It; ++It)
	{
		ACharacter* Character = *It;

		if (Character)
		{
			PlayerCharacter = Character;
			FlockSettings->FlockAttractionPoint = PlayerCharacter->GetActorLocation();
		}
	}

}

void ABoidFlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	FlockSettings->FlockCenter = AverageLocation;
	
	if (PlayerCharacter)
	{
		FlockSettings->FlockAttractionPoint = PlayerCharacter->GetActorLocation();
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


