#include "Actors/BoidFlock.h"

#include "ActorComponents/FlockingComponent.h"
#include "ActorComponents/MessagingComponent.h"

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

	int32 ValidBoidCount = 0;
	for (AActor* Boid : Boids)
	{
		if (IsValid(Boid))
		{
			AverageLocation += Boid->GetActorLocation();
			ValidBoidCount++;
		}
	}

	if (ValidBoidCount > 0)
	{
		AverageLocation /= ValidBoidCount;
	}

	FlockSettings->FlockCenter = AverageLocation;
	
	if (PlayerCharacter)
	{
		FlockSettings->FlockAttractionPoint = PlayerCharacter->GetActorLocation();
	}
}


void ABoidFlock::RegisterBoid(AActor* Boid)
{
	if (!Boid)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "Attempted to register a null Boid in ABoidFlock.");
		return;
	}

	Boids.AddUnique(Boid);
	if (UFlockingComponent* FlockingComp = Boid->FindComponentByClass<UFlockingComponent>())
	{
		FlockingComp->SetFlockManager(this);
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


