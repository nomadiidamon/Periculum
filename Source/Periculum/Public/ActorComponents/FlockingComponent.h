#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlockingComponent.generated.h"

class ABoidFlock;
class USphereComponent;

/**
 * Struct to hold flocking settings for boids
 * TODO: Convert to a data asset for easier tweaking and sharing between different flocks
 */
USTRUCT(BlueprintType)
struct FFlockSettings
{
	GENERATED_BODY()
public:
	/// Cohesion, Separation, Alignment weights and radii, the higher the weight, the more influence that behavior has on the boid's movement
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float CohesionWeight = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float CohesionRadius = 450.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float SeparationWeight = 2.25f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float SeparationRadius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float AlignmentWeight = 1.0f;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float AlignmentRadius = 850.0f;

	/// Speed, Wander strength, and other tuning settings for the boid's movement

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "200.0"))
	float MaxSpeed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "100.0"))
	float MinSpeed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "100.0"))
	float MaxWanderStrength = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "50.0"))
	float MinWanderStrength = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "200.0"))
	float MaxForce = 75.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float TurnSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FVector FlockCenter = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "100.0"))
	float FlockCenterStrength = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FVector FlockAttractionPoint = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "100.0"))
	float FlockAttractionPointStrength = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	bool bDrawDebugRadiusAverage = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	bool bDrawDebugSightLine = false;

	bool operator==(const FFlockSettings& Other) const
	{
		return FMath::IsNearlyEqual(CohesionWeight, Other.CohesionWeight) &&
			FMath::IsNearlyEqual(SeparationWeight, Other.SeparationWeight) &&
			FMath::IsNearlyEqual(AlignmentWeight, Other.AlignmentWeight) &&
			FMath::IsNearlyEqual(CohesionRadius, Other.CohesionRadius) &&
			FMath::IsNearlyEqual(SeparationRadius, Other.SeparationRadius) &&
			FMath::IsNearlyEqual(AlignmentRadius, Other.AlignmentRadius) &&
			FMath::IsNearlyEqual(MaxSpeed, Other.MaxSpeed) &&
			FMath::IsNearlyEqual(MinSpeed, Other.MinSpeed) &&
			FMath::IsNearlyEqual(MaxWanderStrength, Other.MaxWanderStrength)&&
			FMath::IsNearlyEqual(MinWanderStrength, Other.MinWanderStrength)&&
			FMath::IsNearlyEqual(MaxForce, Other.MaxForce)&&
			FMath::IsNearlyEqual(TurnSpeed, Other.TurnSpeed)&&
			FlockCenter.Equals(Other.FlockCenter)&&
			FMath::IsNearlyEqual(FlockCenterStrength, Other.FlockCenterStrength)&&
			FlockAttractionPoint.Equals(Other.FlockAttractionPoint)&&
			FMath::IsNearlyEqual(FlockAttractionPointStrength, Other.FlockAttractionPointStrength)&&
			bDrawDebugRadiusAverage == Other.bDrawDebugRadiusAverage&&
			bDrawDebugSightLine == Other.bDrawDebugSightLine;
	}

};

/// TODO: Create a separate BoidSetting for boids, that is updated/set based on the FlockSettings, so that each boid can have its own settings, but still be influenced by the flock's settings. This will allow for more diverse and dynamic flocking behavior, as individual boids can have unique characteristics while still adhering to the overall flocking rules.


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
	/// The current velocity of the boid. This vector is updated each tick based on the calculated steering forces from cohesion, separation, alignment, and other behaviors.
	/// It represents the direction and speed at which the boid is moving.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	FVector Velocity;

	/// <summary>
	/// The current speed of the boid. This value is used to control the magnitude of the Velocity vector and is clamped between the minimum and maximum speed defined in the FlockSettings.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	float CurrentSpeed = 50.f;

	/// <summary>
	/// The current flock settings that define the behavior of the boid. This struct contains parameters for cohesion, separation, alignment, speed, wander strength, and other tuning settings that influence how the boid moves and interacts with its neighbors.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	FFlockSettings FlockSettings;

public:
	/// <summary>
	/// Sets the flock manager for this boid. This function is used to assign the ABoidFlock instance that manages the flocking behavior of this boid. 
	/// It should be called when the boid is registered with the flock, or transfered to a new flock to ensure it has a reference to the flock manager for accessing flock settings and other relevant data.
	/// </summary>
	/// <param name="Manager">The ABoidFlock instance that manages the flocking behavior of this boid.</param>
	void SetFlockManager(ABoidFlock* Manager) { FlockManager = Manager; }

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
	/// Updates the flock settings for this boid based on the new settings provided by the flock manager. 
	/// This function is called when the flock settings are changed, and it updates the boid's internal settings to match the new configuration.
	/// </summary>
	/// <param name="NewSettings">The new flock settings for the boid.</param>
	UFUNCTION()
	void UpdateFlockSettings(const struct FFlockSettings& NewSettings);

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
