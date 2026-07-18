// Fill out your copyright notice in the Description page of Project Settings.

/// @file BoidFlockSettings.h
/// @brief Data asset that holds flocking settings for boids, allowing for easy configuration and tuning of flocking behavior in the editor.
/// @note This is for the entire flock, not individual boids. Individual boids can have their own settings (FBoidSettings), but they will be influenced by the flock's settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BoidFlockSettings.generated.h"

/**
 * Struct to hold flocking settings for boids
 */
UCLASS()
class PERICULUM_API UBoidFlockSettings : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/// <summary>
	/// The weight applied to the cohesion behavior of the boids. 
	/// This value determines how strongly a boid will steer towards the average position of its neighbors, promoting flocking behavior. 
	/// A higher value results in stronger cohesion, while a lower value allows for more independent movement.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float CohesionWeight = 1.0f;

	/// <summary>
	/// The weight applied to the separation behavior of the boids. 
	/// This value determines how strongly a boid will steer away from its neighbors to avoid crowding, promoting separation within the flock. 
	/// A higher value results in stronger separation, while a lower value allows for closer proximity between boids.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float SeparationWeight = 2.25f;

	/// <summary>
	/// The weight applied to the alignment behavior of the boids. 
	/// This value determines how strongly a boid will align its velocity with its neighbors, promoting synchronized movement within the flock. 
	/// A higher value results in stronger alignment, while a lower value allows for more independent movement.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float AlignmentWeight = 1.0f;

	/// <summary>
	/// The maximum speed that a boid can achieve. 
	/// This value is used to limit the boid's velocity, ensuring that it does not exceed a certain threshold.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "10000.0"))
	float MaxSpeed = 200.0f;

	/// <summary>
	/// The minimum speed that a boid can achieve.
	/// This value is used to ensure that the boid maintains a certain level of movement, preventing it from coming to a complete stop.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "5000.0"))
	float MinSpeed = 20.0f;

	/// <summary>
	/// The maximum strength of the wander behavior applied to the boids.
	/// This value determines how much random movement is introduced to the boid's behavior, allowing for more natural and unpredictable movement patterns.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "10000.0"))
	float MaxWanderStrength = 200.0f;

	/// <summary>
	/// The minimum strength of the wander behavior applied to the boids.
	/// This value determines the lower limit of random movement introduced to the boid's behavior, ensuring that there is always some level of unpredictability in its movement patterns.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "5000.0"))
	float MinWanderStrength = 20.0f;

	/// <summary>
	/// The maximum force that can be applied to a boid when steering.
	/// This value is used to limit the amount of force that can be applied to change the boid's velocity, ensuring that it does not accelerate too quickly or unrealistically.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxForce = 75.0f;

	/// <summary>
	/// The speed at which a boid can turn to align with its neighbors or change direction.
	/// This value determines how quickly a boid can adjust its orientation, allowing for more responsive and dynamic movement.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float TurnSpeed = 2.0f;

	/// <summary>
	/// The point in space that represents the center of the flock. This is updated by the flock manager and is used to maintain cohesion among the boids, ensuring they stay together as a group.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FVector FlockCenter = FVector::ZeroVector;

	/// <summary>
	/// The strength of the attraction force towards the flock center. This value determines how strongly a boid will steer towards the average position of all boids in the flock, helping to keep the flock together.
	/// A higher value results in stronger attraction, while a lower value allows for more independent movement.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100000.0"))
	float FlockCenterStrength = 2.0f;

	/// <summary>
	/// The point in space that the boid is attracted to. This vector can be used to influence the boid's movement towards a specific location, such as a target or goal within the flocking simulation.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FVector FlockAttractionPoint = FVector::ZeroVector;

	/// <summary>
	/// The strength of the attraction force towards the flock attraction point. This value determines how strongly a boid will steer towards the specified attraction point, allowing for targeted movement within the flocking simulation.
	/// A higher value results in stronger attraction, while a lower value allows for more independent movement.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100000.0"))
	float FlockAttractionPointStrength = 2.0f;

	bool operator==(const UBoidFlockSettings& Other) const
	{
		return FMath::IsNearlyEqual(CohesionWeight, Other.CohesionWeight) &&
			FMath::IsNearlyEqual(SeparationWeight, Other.SeparationWeight) &&
			FMath::IsNearlyEqual(AlignmentWeight, Other.AlignmentWeight) &&
			FMath::IsNearlyEqual(MaxSpeed, Other.MaxSpeed) &&
			FMath::IsNearlyEqual(MinSpeed, Other.MinSpeed) &&
			FMath::IsNearlyEqual(MaxWanderStrength, Other.MaxWanderStrength) &&
			FMath::IsNearlyEqual(MinWanderStrength, Other.MinWanderStrength) &&
			FMath::IsNearlyEqual(MaxForce, Other.MaxForce) &&
			FMath::IsNearlyEqual(TurnSpeed, Other.TurnSpeed) &&
			FlockCenter.Equals(Other.FlockCenter) &&
			FMath::IsNearlyEqual(FlockCenterStrength, Other.FlockCenterStrength) &&
			FlockAttractionPoint.Equals(Other.FlockAttractionPoint) &&
			FMath::IsNearlyEqual(FlockAttractionPointStrength, Other.FlockAttractionPointStrength);
	}
};
