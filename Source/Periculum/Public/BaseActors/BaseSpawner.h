#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Defines/SpawnModes.h"
#include "BaseSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnModeChanged, ESpawnMode, NewSpawnMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnableActorSpawned, AActor*, SpawnedActor);

class USphereSpawnerComponent;
class UBoxSpawnerComponent;
class UCapsuleSpawnerComponent;
class APericulumCharacter;

/**
 * ABaseSpawner is an actor that can spawn other actors based on different spawn modes and location modes.
 * It supports spawning actors in a sphere, box, capsule, or random mode, and can be customized for specific spawn behavior.
 */ 

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
	/// <summary>
	/// Dynamic multicast delegate that is called when the spawn mode changes. It broadcasts the new spawn mode to any bound listeners.
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "Spawning")
	FOnSpawnModeChanged OnSpawnModeChanged;

	/// <summary>
	/// Dynamic multicast delegate that is called when a spawnable actor is spawned. It broadcasts the spawned actor to any bound listeners.
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "Spawning")
	FOnSpawnableActorSpawned OnSpawnableActorSpawned;

	/// <summary>
	/// Handler function for when the spawn mode changes. It updates the spawn mode and switches to the appropriate spawning logic based on the new mode.
	/// </summary>
	/// <param name="NewSpawnMode"></param>
	UFUNCTION()
	virtual void HandleSpawnModeChanged(ESpawnMode NewSpawnMode);

	/// <summary>
	/// Handler function for when an actor is spawned. It broadcasts the spawned actor to any bound listeners.
	/// </summary>
	/// <param name="SpawnedActor"></param>
	UFUNCTION()
	virtual void HandleActorSpawned(AActor* SpawnedActor);

public:	
	/// <summary>
	/// The class of the actor to spawn. This can be set in the editor or at runtime to specify which actor type should be spawned by this spawner.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;

	/// <summary>
	/// The array of spawned actors. This keeps track of all actors that have been spawned by this spawner, allowing for management and cleanup of spawned actors.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<TSubclassOf<AActor>> SpawnedActors;

	/// <summary>
	/// The spawn mode for this spawner. It determines the shape or method used for spawning actors (e.g., sphere, box, capsule, random, or custom).
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	ESpawnMode SpawnMode = ESpawnMode::Box;

	/// <summary>
	/// The spawn location mode for this spawner. It determines whether actors are spawned inside or on the surface of the specified shape.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	ESpawnLocationMode LocationMode = ESpawnLocationMode::InsideShape;
	
	/// <summary>
	/// The SphereSpawnerComponent is responsible for handling spawning logic when the spawn mode is set to Sphere. It provides functionality for generating spawn locations and parameters based on a sphere shape.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	USphereSpawnerComponent* SphereSpawnerComponent;

	/// <summary>
	/// The BoxSpawnerComponent is responsible for handling spawning logic when the spawn mode is set to Box. It provides functionality for generating spawn locations and parameters based on a box shape.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	UBoxSpawnerComponent* BoxSpawnerComponent;

	/// <summary>
	/// The CapsuleSpawnerComponent is responsible for handling spawning logic when the spawn mode is set to Capsule. It provides functionality for generating spawn locations and parameters based on a capsule shape.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	UCapsuleSpawnerComponent* CapsuleSpawnerComponent;

	/// <summary>
	/// The interval at which actors are spawned, in seconds. This determines how frequently the spawner will attempt to spawn new actors based on the specified spawn mode and location mode.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnInterval = 0.5f;

	/// <summary>
	/// The maximum number of actors that can be spawned by this spawner. Once this limit is reached, the spawner will stop spawning new actors until some are removed or the limit is increased.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 MaxSpawnCount = 100;

	/// <summary>
	/// The flag indicating whether the spawner is currently allowed to spawn actors. If set to false, the spawner will not spawn any new actors until this flag is set back to true.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	bool bCanSpawn = true;

	/// <summary>
	/// Whether to draw debug information for the spawner. If set to true, the spawner will visualize its spawn area and other relevant information in the editor or during gameplay for debugging purposes.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	bool bDrawDebug = false;

	/// <summary>
	/// Timer handle to manage the spawning interval. It is used to schedule the SpawnActor function to be called at regular intervals based on the specified SpawnInterval.
	/// </summary>
	FTimerHandle SpawnTimerHandle;

	/// <summary>
	/// The reference to the player character in the game. This can be used to interact with the player or to determine spawn behavior based on the player's location or state.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	APericulumCharacter* Player;

public:
	/// <summary>
	/// Spawns an actor based on the current spawn mode and location mode.
	/// This function is called at regular intervals defined by SpawnInterval and handles the logic for spawning actors in the appropriate shape or method.
	/// </summary>
	UFUNCTION()
	void SpawnActor();

	/// <summary>
	/// Spawns an actor in a spherical area based on the SphereSpawnerComponent's parameters.
	/// This function is called when the spawn mode is set to Sphere and generates a spawn location within or on the surface of the sphere.
	/// </summary>
	/// <returns>The spawned actor, or nullptr if spawning failed.</returns>
	UFUNCTION()
	AActor* SpawnActor_Sphere();
	
	/// <summary>
	/// Spawns an actor in a box-shaped area based on the BoxSpawnerComponent's parameters.
	/// This function is called when the spawn mode is set to Box and generates a spawn location within or on the surface of the box.
	/// </summary>
	/// <returns>The spawned actor, or nullptr if spawning failed.</returns>
	UFUNCTION()
	AActor* SpawnActor_Box();

	/// <summary>
	/// Spawns an actor in a capsule-shaped area based on the CapsuleSpawnerComponent's parameters.
	/// This function is called when the spawn mode is set to Capsule and generates a spawn location within or on the surface of the capsule.	
	/// </summary>
	/// <returns>The spawned actor, or nullptr if spawning failed.</returns>
	UFUNCTION()
	AActor* SpawnActor_Capsule();

	/// <summary>
	/// Spawns an actor at a random location based on the current spawn mode and location mode.
	/// This function is called when the spawn mode is set to Random and generates a spawn location within the defined spawn area.
	/// </summary>
	/// <returns>The spawned actor, or nullptr if spawning failed.</returns>
	UFUNCTION()
	AActor* SpawnActor_Random();

	/// <summary>
	/// Spawns an actor using custom logic defined by the user.
	/// This function is called when the spawn mode is set to Custom and allows for user-defined spawning behavior.
	/// </summary>
	/// <returns>The spawned actor, or nullptr if spawning failed.</returns>
	UFUNCTION()
	virtual AActor* SpawnActor_Custom();

	/// <summary>
	/// Called when the spawn mode changes. It switches the spawning logic to the appropriate method based on the new spawn mode.
	/// </summary>
	UFUNCTION()
	virtual void SwitchMode();

	/// <summary>
	/// Handler function for when the bCanSpawn flag changes. It starts or stops the spawning timer based on the new value of bCanSpawn.
	/// </summary>
	UFUNCTION()
	void HandleCanSpawnChanged();

};
