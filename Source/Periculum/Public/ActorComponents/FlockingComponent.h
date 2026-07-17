// Fill out your copyright notice in the Description page of Project Settings.

/// @file FlockingComponent.h
/// @brief Component that implements flocking behavior for boids, allowing them to move and interact as a cohesive group based on configurable settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlockingComponent.generated.h"

class ABoidFlock;
class USphereComponent;

/**
* FBoidSettings struct defines the parameters that control the flocking behavior of boids, including cohesion, separation, alignment, and other relevant properties.
*/
USTRUCT(BlueprintType)
struct FBoidSettings 
{
	GENERATED_BODY()

	/// <summary>
	/// The radius within which the boid will steer towards the average position of neighboring boids to maintain cohesion. This value is used to determine how far the boid will look for other boids to stay together as a group, promoting flocking behavior.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float CohesionRadius = 450.0f;

	/// <summary>
	/// The radius within which the boid will steer away from neighboring boids to avoid crowding. This value is used to determine how far the boid will look for other boids to maintain a comfortable distance, preventing collisions and promoting separation within the flock.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float SeparationRadius = 300.0f;

	/// <summary>
	/// The radius within which the boid will align its velocity with neighboring boids. This value is used to determine how far the boid will look for other boids to match its direction and speed, promoting synchronized movement within the flock.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float AlignmentRadius = 850.0f;

	/// <summary>
	/// The point in space that represents the center of the flock. This is updated by the flock manager and is used to maintain cohesion among the boids, ensuring they stay together as a group.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FVector FlockCenter = FVector::ZeroVector;

	/// <summary>
	/// The point in space that the boid is attracted to. This vector can be used to influence the boid's movement towards a specific location, such as a target or goal within the flocking simulation.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FVector AttractionPoint = FVector::ZeroVector;

	/// <summary>
	/// The current velocity of the boid. This vector is updated each tick based on the calculated steering forces from cohesion, separation, alignment, and other behaviors.
	/// It represents the direction and speed at which the boid is moving.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	FVector Velocity = FVector::ZeroVector;

	/// <summary>
	/// The current speed of the boid.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	float CurrentSpeed = 50.f;

	/// <summary>
	/// The strength of the avoidance force applied to the boid when it detects an obstacle or another boid within its avoidance radius. This value determines how strongly the boid will steer away from potential collisions, helping to maintain separation and prevent overcrowding within the flock.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	float AvoidanceStrength = 100.f;
};


/**
* UFlockingComponent is an Actor Component that implements flocking behavior for boid actors.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERICULUM_API UFlockingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFlockingComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// The flock manager that controls the flocking behavior of this boid. This should be set to a valid instance of ABoidFlock that manages the flock.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<ABoidFlock> FlockManager;

	/// <summary>
	/// The sphere component used to detect overlapping actors for flocking behavior.
	/// This component should be set up to trigger overlap events and is used to determine neighboring boids for cohesion, separation, and alignment calculations.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<USphereComponent> OverlappingSphereComponent;

	/// <summary>
	/// The array of actors that are currently overlapping with the OverlappingSphereComponent.
	/// This array is updated during overlap events and is used to calculate the flocking behavior based on nearby boids.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TArray<TObjectPtr<AActor>> OverlappingActors;

	/// <summary>
	/// The settings that control the flocking behavior of this boid. These settings include parameters for cohesion, separation, alignment, and other behaviors that influence how the boid interacts with its neighbors and moves as part of the flock.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	FBoidSettings BoidSettings;

public:
	/// <summary>
	/// Sets the flock manager for this boid. This function is used to assign the ABoidFlock instance that manages the flocking behavior of this boid. 
	/// It should be called when the boid is registered with the flock, or transfered to a new flock to ensure it has a reference to the flock manager for accessing flock settings and other relevant data.
	/// </summary>
	/// <param name="Manager">The ABoidFlock instance that manages the flocking behavior of this boid.</param>
	void SetFlockManager(ABoidFlock* Manager) { FlockManager = Manager; }

	/// <summary>
	/// This function should be called from the owning Boid/BoidFlock to direct the Flocking component to avoid an obstacle.
	/// It calculates the avoidance direction based on the location and normal of the obstacle, as well as the current velocity of the boid, and applies it to steer the boid away from potential collisions.
	/// </summary>
	/// <param name="ObstacleLocation">The location of the obstacle.</param>
	/// <param name="ObstacleNormal">The normal vector of the obstacle's surface.</param>
	/// <param name="CurrentVelocity">The current velocity of the boid.</param>
	void AvoidObstacle(FVector ObstacleLocation, FVector ObstacleNormal, FVector CurrentVelocity);


	/// <summary>
	/// Calculates the cohesion vector for the boid based on the positions of its neighboring boids. 
	/// Cohesion is the behavior that causes a boid to move towards the average position of its neighbors, helping to keep the flock together.
	/// </summary>
	/// <param name="Neighbors">The array of neighboring boids.</param>
	/// <returns>The calculated cohesion vector.</returns>
	FVector CalculateCohesion(TArray<AActor*> Neighbors);

	/// <summary>
	/// Calculates the separation vector for the boid based on the positions of its neighboring boids.
	/// Separation is the behavior that causes a boid to steer away from its neighbors to avoid crowding.
	/// </summary>
	/// <param name="Neighbors">The array of neighboring boids.</param>
	/// <returns>The calculated separation vector.</returns>
	FVector CalculateSeparation(TArray<AActor*> Neighbors);

	/// <summary>
	/// Calculates the alignment vector for the boid based on the velocities of its neighboring boids.
	/// Alignment is the behavior that causes a boid to match the velocity of its neighbors.
	/// </summary>
	/// <param name="Neighbors">The array of neighboring boids.</param>
	/// <returns>The calculated alignment vector.</returns>
	FVector CalculateAlignment(TArray<AActor*> Neighbors);

	/// <summary>
	/// Calculates the overall steering force for the boid based on the cohesion, separation, and alignment vectors.
	/// </summary>
	/// <param name="Cohesion">The calculated cohesion vector.</param>
	/// <param name="Separation">The calculated separation vector.</param>
	/// <param name="Alignment">The calculated alignment vector.</param>
	/// <returns>The overall steering force vector.</returns>
	FVector CalculateSteeringForce_Boid(FVector Cohesion, FVector Separation, FVector Alignment);

	/// <summary>
	/// Calculates the wander vector for the boid, which introduces random movement to simulate natural wandering behavior.
	/// Wander is used to prevent the flock from moving in a perfectly straight line and adds variability to the boid's movement.
	/// </summary>
	/// <returns>The change in position for the boid.</returns>
	FVector CalculateWander();

	/// <summary>
	/// Calculates the attraction vector towards the center of the flock, which helps to keep the boid moving towards the average position of all boids in the flock.
	/// </summary>
	/// <returns>The calculated flock center attraction vector.</returns>
	FVector CalculateFlockCenterAttraction();

	/// <summary>
	/// Calculates the attraction vector towards a specific point of interest for the flock, which can be used to guide the flock towards a target location or goal.
	/// </summary>
	/// <returns>The calculated flock attraction point vector.</returns>
	FVector CalculateFlockAttractionPoint();

	/// <summary>
	/// Calculates the overall steering force for the boid based on the wander vector, flock center attraction, and flock attraction point.
	/// </summary>
	/// <param name="Wander">The calculated wander vector.</param>
	/// <param name="FlockCenter">The calculated flock center attraction vector.</param>
	/// <param name="FlockAttraction">The calculated flock attraction point vector.</param>
	/// <returns>The overall steering force vector.</returns>
	FVector CalculateSteeringForce_Tuning(FVector Wander, FVector FlockCenter, FVector FlockAttraction);

	/// <summary>
	/// Calculates the new velocity for the boid based on the current velocity and the calculated steering forces.
	/// </summary>
	/// <param name="CurrentVelocity">The current velocity of the boid.</param>
	void CalculateVelocity(FVector CurrentVelocity);

	/// <summary>
	/// Draws visual/debug bounds for components used in overlap detection.
	/// </summary>
	UFUNCTION()
	void DrawOverlapComponentBounds();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
