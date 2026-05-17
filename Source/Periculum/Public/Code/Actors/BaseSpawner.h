#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Code/Utility/SpawnModes.h"
#include "BaseSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnModeChanged, ESpawnMode, NewSpawnMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnableActorSpawned, AActor*, SpawnedActor);

class USphereSpawnerComponent;
class UBoxSpawnerComponent;
class UCapsuleSpawnerComponent;
class APericulumCharacter;

UCLASS()
class PERICULUM_API ABaseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseSpawner();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Spawning")
	FOnSpawnModeChanged OnSpawnModeChanged;

	UPROPERTY(BlueprintAssignable, Category = "Spawning")
	FOnSpawnableActorSpawned OnSpawnableActorSpawned;

	UFUNCTION()
	virtual void HandleSpawnModeChanged(ESpawnMode NewSpawnMode);

	UFUNCTION()
	virtual void HandleActorSpawned(AActor* SpawnedActor);

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<TSubclassOf<AActor>> SpawnedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	ESpawnMode SpawnMode = ESpawnMode::Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	ESpawnLocationMode LocationMode = ESpawnLocationMode::InsideShape;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	USphereSpawnerComponent* SphereSpawnerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	UBoxSpawnerComponent* BoxSpawnerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	UCapsuleSpawnerComponent* CapsuleSpawnerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnInterval = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 MaxSpawnCount = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	bool bCanSpawn = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	bool bDrawDebug = false;

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	APericulumCharacter* Player;

public:

	UFUNCTION()
	void SpawnActor();

	UFUNCTION()
	AActor* SpawnActor_Sphere();

	UFUNCTION()
	AActor* SpawnActor_Box();

	UFUNCTION()
	AActor* SpawnActor_Capsule();

	UFUNCTION()
	AActor* SpawnActor_Random();

	UFUNCTION()
	virtual AActor* SpawnActor_Custom();

	UFUNCTION()
	virtual void SwitchMode();

};
