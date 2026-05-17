#include "Code/Actors/BaseSpawner.h"

#include "Code/Components/SphereSpawnerComponent.h"
#include "Components/SphereComponent.h"

#include "Code/Components/BoxSpawnerComponent.h"
#include "Components/BoxComponent.h"

#include "Code/Components/CapsuleSpawnerComponent.h"
#include "Components/CapsuleComponent.h"

#include "Code/Utility/PericulumLog.h"

ABaseSpawner::ABaseSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SphereSpawnerComponent = CreateDefaultSubobject<USphereSpawnerComponent>(TEXT("SphereSpawnerComponent"));
	SphereSpawnerComponent->SphereComponent->SetupAttachment(RootComponent);

	BoxSpawnerComponent = CreateDefaultSubobject<UBoxSpawnerComponent>(TEXT("BoxSpawnerComponent"));
	BoxSpawnerComponent->BoxComponent->SetupAttachment(RootComponent);

	CapsuleSpawnerComponent = CreateDefaultSubobject<UCapsuleSpawnerComponent>(TEXT("CapsuleSpawnerComponent"));
	CapsuleSpawnerComponent->CapsuleComponent->SetupAttachment(RootComponent);
}

void ABaseSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ABaseSpawner::SpawnActor, SpawnInterval, true);
}

void ABaseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseSpawner::HandleSpawnModeChanged(ESpawnMode NewSpawnMode)
{
	SpawnMode = NewSpawnMode;
	SwitchMode();
	if (OnSpawnModeChanged.IsBound())
		OnSpawnModeChanged.Broadcast(NewSpawnMode);
}

void ABaseSpawner::HandleActorSpawned(AActor* SpawnedActor)
{
	if (OnSpawnableActorSpawned.IsBound())
		OnSpawnableActorSpawned.Broadcast(SpawnedActor);
}

void ABaseSpawner::SpawnActor()
{
	if (!bCanSpawn)
	{
		return;
	}

	if (SpawnedActors.Num() >= MaxSpawnCount)
	{
		bCanSpawn = false;
		PERICULUM_LOG(Periculum_Game, Warning, "Max spawn count reached in BaseSpawner. No more actors will be spawned until some are removed.");
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	AActor* spawnedActor = nullptr;
	switch (SpawnMode)
	{
	case ESpawnMode::Sphere:
		spawnedActor = SpawnActor_Sphere();
		break;

	case ESpawnMode::Box:
		spawnedActor = SpawnActor_Box();
		break;

	case ESpawnMode::Capsule:
		spawnedActor = SpawnActor_Capsule();
		break;

	case ESpawnMode::Random:
		spawnedActor = SpawnActor_Random();
		break;

	case ESpawnMode::Custom:
		spawnedActor = SpawnActor_Custom();
		break;

	default:
		PERICULUM_LOG(Periculum_Game, Warning, "Invalid SpawnMode in BaseSpawner. Please select a valid spawn mode.");
		break;
	}
	
	if (spawnedActor) {
		HandleActorSpawned(spawnedActor);
	}
}

AActor* ABaseSpawner::SpawnActor_Sphere()
{
	if (!ActorToSpawn) {
		PERICULUM_LOG(Periculum_Game, Warning, "ActorToSpawn is not assigned in BaseSpawner. Please assign an actor class to spawn.");
		return nullptr;
	}
	if (!SphereSpawnerComponent || !SphereSpawnerComponent->SphereComponent) {
		PERICULUM_LOG(Periculum_Game, Warning, "SphereSpawnerComponent or its SphereComponent is not assigned in BaseSpawner. Please ensure SphereSpawnerComponent and its SphereComponent are properly set up.");
		return nullptr;
	}
	SwitchMode();
	FSphereSpawnData SpawnData = SphereSpawnerComponent->GenerateAndStoreSpawnData();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnData.SpawnTransform.GetLocation(),
		SpawnData.SpawnTransform.GetRotation().Rotator(), SpawnParams);
	SpawnedActors.Add(ActorToSpawn);

	return spawnedActor;
}

AActor* ABaseSpawner::SpawnActor_Box()
{
	if (!ActorToSpawn) {
		PERICULUM_LOG(Periculum_Game, Warning, "ActorToSpawn is not assigned in BaseSpawner. Please assign an actor class to spawn.");
		return nullptr;
	}
	if (!BoxSpawnerComponent || !BoxSpawnerComponent->BoxComponent) {
		PERICULUM_LOG(Periculum_Game, Warning, "BoxSpawnerComponent or its BoxComponent is not assigned in BaseSpawner. Please ensure BoxSpawnerComponent and its BoxComponent are properly set up.");
		return nullptr;
	}
	SwitchMode();
	FBoxSpawnData SpawnData = BoxSpawnerComponent->GenerateAndStoreSpawnData();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnData.SpawnTransform.GetLocation(),
		SpawnData.SpawnTransform.GetRotation().Rotator(), SpawnParams);
	SpawnedActors.Add(ActorToSpawn);
	return spawnedActor;
}

AActor* ABaseSpawner::SpawnActor_Capsule()
{
	if (!ActorToSpawn) {
		PERICULUM_LOG(Periculum_Game, Warning, "ActorToSpawn is not assigned in BaseSpawner. Please assign an actor class to spawn.");
		return nullptr;
	}
	if (!CapsuleSpawnerComponent || !CapsuleSpawnerComponent->CapsuleComponent) {
		PERICULUM_LOG(Periculum_Game, Warning, "CapsuleSpawnerComponent or its CapsuleComponent is not assigned in BaseSpawner. Please ensure CapsuleSpawnerComponent and its CapsuleComponent are properly set up.");
		return nullptr;
	}
	SwitchMode();
	FCapsuleSpawnData SpawnData = CapsuleSpawnerComponent->GenerateAndStoreSpawnData();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnData.SpawnTransform.GetLocation(),
		SpawnData.SpawnTransform.GetRotation().Rotator(), SpawnParams);
	SpawnedActors.Add(ActorToSpawn);
	return spawnedActor;
}

AActor* ABaseSpawner::SpawnActor_Random()
{
	int value = FMath::RandRange(0, 2);
	AActor* spawnedActor = nullptr;
	switch (value)
	{
	case 0:
		spawnedActor = SpawnActor_Sphere();
		break;

	case 1:
		spawnedActor = SpawnActor_Box();
		break;

	case 2:
		spawnedActor = SpawnActor_Capsule();
		break;

	default:
		PERICULUM_LOG(Periculum_Game, Warning, "Invalid random value generated in SpawnActor_Random. This should never happen.");
		break;
	}
	return spawnedActor;
}

AActor* ABaseSpawner::SpawnActor_Custom()
{
	return nullptr;
}

void ABaseSpawner::SwitchMode()
{
	switch (SpawnMode)
	{
	case ESpawnMode::Sphere:
		BoxSpawnerComponent->SetComponentTickEnabled(false);
		BoxSpawnerComponent->bDebugDrawArea = !bDrawDebug;
		CapsuleSpawnerComponent->SetComponentTickEnabled(false);
		CapsuleSpawnerComponent->bDebugDrawArea = !bDrawDebug;
		SphereSpawnerComponent->SetComponentTickEnabled(true);
		SphereSpawnerComponent->SpawnParams.LocationMode = LocationMode;
		SphereSpawnerComponent->bDebugDrawArea = bDrawDebug;
		break;
	case ESpawnMode::Box:
		SphereSpawnerComponent->SetComponentTickEnabled(false);
		SphereSpawnerComponent->bDebugDrawArea = !bDrawDebug;
		CapsuleSpawnerComponent->SetComponentTickEnabled(false);
		CapsuleSpawnerComponent->bDebugDrawArea = !bDrawDebug;
		BoxSpawnerComponent->SetComponentTickEnabled(true);
		BoxSpawnerComponent->SpawnParams.LocationMode = LocationMode;
		BoxSpawnerComponent->bDebugDrawArea = bDrawDebug;
		break;
	case ESpawnMode::Capsule:
		SphereSpawnerComponent->SetComponentTickEnabled(false);
		SphereSpawnerComponent->bDebugDrawArea = !bDrawDebug;
		BoxSpawnerComponent->SetComponentTickEnabled(false);
		BoxSpawnerComponent->bDebugDrawArea = !bDrawDebug;
		CapsuleSpawnerComponent->SetComponentTickEnabled(true);
		CapsuleSpawnerComponent->SpawnParams.LocationMode = LocationMode;
		CapsuleSpawnerComponent->bDebugDrawArea = bDrawDebug;
		break;
	default:
		break;
	}
}
