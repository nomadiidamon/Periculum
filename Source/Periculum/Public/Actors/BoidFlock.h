// Fill out your copyright notice in the Description page of Project Settings.

/// @file BoidFlock.h
/// @brief ABoidFlock class is responsible for managing a flock of boids, including spawning, registering, and coordinating their behavior based on flocking rules and settings.

#pragma once
#include "CoreMinimal.h"
#include "BaseActors/BaseSpawner.h"
#include "ActorComponents/FlockingComponent.h"
#include "BoidFlock.generated.h"


class ABoid;

class UMessagingComponent;

class UBoidFlockSettings;

/**
 * ABoidFlock class is responsible for managing a flock of boids.
 */

UCLASS()
class PERICULUM_API ABoidFlock : public ABaseSpawner
{
	GENERATED_BODY()

public:
	ABoidFlock();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/// <summary>
	/// The class type of the boid actor to spawn. This should be set to a valid subclass of AActor that represents the boid.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock")
	TSubclassOf<AActor> BoidClass;

	/// <summary>
	/// The messaging component used for communication between the flock and its boids. This component is responsible for broadcasting messages to the boids and receiving messages from them, allowing for coordinated flocking behavior.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock")
	TObjectPtr<UMessagingComponent> MessagingComponent;

	/// <summary>
	/// The settings that control the flocking behavior of the boids in this flock. This should be set to a valid instance of UBoidFlockSettings that contains parameters for cohesion, separation, alignment, and other behaviors.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	TObjectPtr<UBoidFlockSettings> FlockSettings;

public:
	/// <summary>
	/// Registers a boid actor with the flock, adding it to the internal list of boids and updating its flocking component with the current flock settings.
	/// </summary>
	/// <param name="Boid"></param>
	UFUNCTION()
	void RegisterBoid(AActor* Boid);

	/// <summary>
	/// Spawns a number of boid actors based on the current flock settings and adds them to the flock. This function is responsible for initializing the flock with the specified number of boids.
	/// </summary>
	UFUNCTION()
	void SpawnBoids();

	/// <summary>
	/// Returns an array of neighboring boid actors within a specified radius of the given boid. This function is used to determine which boids are close enough to influence each other's behavior according to the flocking rules.
	/// </summary>
	/// <param name="Boid">The boid actor to check for neighbors.</param>
	/// <param name="Radius">The radius within which to search for neighboring boids.</param>
	/// <returns>The array of neighboring boid actors.</returns>
	UFUNCTION()
	TArray<AActor*> GetNeighboringBoids(AActor* Boid, float Radius) const;

protected:
	/// <summary>
	/// The complete list of boid actors that are part of this flock. This array is used to manage and update the flocking behavior of all registered boids.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock")
	TArray<AActor*> Boids;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock")
	TObjectPtr<ACharacter> PlayerCharacter;
};
