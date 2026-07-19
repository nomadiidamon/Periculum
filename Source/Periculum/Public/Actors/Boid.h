// Fill out your copyright notice in the Description page of Project Settings.

/// @file Boid.h
/// @brief ABoid class represents an individual boid in a flocking simulation. It contains a FlockingComponent that handles the flocking behavior and a StaticMeshComponent for visual representation.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

class UStaticMeshComponent;
class USkeletalMeshComponent;
class USphereComponent;

class UFlockingComponent;
class UTraceComponent;
class UMessagingComponent;
class UTagContainerComponent;

class UBoidFlockSettings;

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

	UFUNCTION(BlueprintCallable, Category = "Components")
	UTagContainerComponent* GetTagContainer() const { return TagContainer; }

public:	
	/// <summary>
	/// The StaticMeshComponent used for visual representation of the Boid.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<USphereComponent> CollisionComponent;

	/// <summary>
	/// The FlockingComponent responsible for handling the flocking behavior of this Boid.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<UFlockingComponent> FlockingComponent;

	/// <summary>
	/// The TraceComponent used for line tracing and collision detection in the Boid's flocking behavior.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<UTraceComponent> TraceComponent;

	/// <summary>
	/// The MessagingComponent used for communication between Boids and the FlockManager.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<UMessagingComponent> MessagingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<UTagContainerComponent> TagContainer;

protected:
	UFUNCTION()
	void HandleObstacleDetection(FTracePolicyResult Result);

};
