#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

class UFlockingComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class USphereComponent;
struct FFlockSettings;

/**
 * ABoid class represents an individual boid in a flocking simulation.
 * It contains a FlockingComponent that handles the flocking behavior and a StaticMeshComponent for visual representation.
 */

UCLASS()
class PERICULUM_API ABoid : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoid();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/// <summary>
	/// Returns the FlockingComponent associated with this Boid.
	/// </summary>
	/// <returns>The FlockingComponent instance if valid, otherwise nullptr.</returns>
	UFUNCTION()
	UFlockingComponent* GetFlockingComponent() const { return FlockingComponent; }

public:	
	/// <summary>
	/// The FlockingComponent responsible for handling the flocking behavior of this Boid.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	UFlockingComponent* FlockingComponent;

	/// <summary>
	/// The StaticMeshComponent used for visual representation of the Boid.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	UStaticMeshComponent* StaticMeshComponent;

	/// <summary>
	/// Bool to determine whether to draw debug radius for the Boid's flocking behavior.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	bool bDrawDebugRadius = false;

	/// <summary>
	/// Bool to determine whether to draw debug sight line for the Boid's flocking behavior.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	bool bDrawDebugSightLine = false;

public:
	/// <summary>
	/// A function to update the flock settings of the Boid's FlockingComponent.
	/// </summary>
	/// <param name="NewSettings">The new flock settings to apply.</param>
	void UpdateFlockSettings(const FFlockSettings& NewSettings);

};
