// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActors/BaseSpawner.h"
#include "ActorComponents/FlockingComponent.h"
#include "BoidFlock.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlockSettingsChanged, const FFlockSettings&, NewSettings);

class ABoid;

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
	/// Dynamic multicast delegate that is triggered when the flock settings are changed.
	/// </summary>
	FOnFlockSettingsChanged OnFlockSettingsChanged;

public:
	/// <summary>
	/// The class type of the boid actor to spawn. This should be set to a valid subclass of AActor that represents the boid.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock")
	TSubclassOf<AActor> BoidClass;

	/// <summary>
	/// Property that holds configuration settings for flocking behavior, exposed to the editor and Blueprints.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FFlockSettings FlockSettings;

	/// <summary>
	/// The last known flock settings, used to detect changes and trigger updates to the boids.
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FFlockSettings LastFlockSettings;

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

	/// <summary>
	/// Updates the flock settings for all registered boids in the flock. This function is called when the flock settings are changed, and it propagates the new settings to each boid's flocking component to ensure consistent behavior across the flock.
	/// </summary>
	/// <param name="NewSettings"></param>
	UFUNCTION()
	void UpdateBoidSettings(const FFlockSettings& NewSettings);
};
