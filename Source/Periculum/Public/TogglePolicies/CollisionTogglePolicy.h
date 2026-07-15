// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "CollisionTogglePolicy.generated.h"

/**
 * Enum representing the different collision toggle modes.
 */
UENUM(BlueprintType)
enum class ECollisionToggleMode : uint8
{
	NoCollision UMETA(DisplayName = "No Collision"),
	QueryOnly UMETA(DisplayName = "Query Only"),
	PhysicsOnly UMETA(DisplayName = "Physics Only"),
	QueryAndPhysics UMETA(DisplayName = "Query and Physics"),
};

/**
 * A toggle policy that controls the collision settings of a target object.
 */
UCLASS(EditInlineNew)
class PERICULUM_API UCollisionTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	
public:
	/// <summary>
	/// The collision mode to apply when the policy is disabled. This determines how the target object's collision settings will be modified when the policy is not active.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionTogglePolicy")
	ECollisionToggleMode DisableMode = ECollisionToggleMode::NoCollision;

	virtual void Apply_Implementation(UObject* Target, bool bEnable) override;

private:
	/// <summary>
	/// A map that stores the original collision settings of the target object's primitive components. This is used to restore the original settings when the policy is disabled.
	/// </summary>
	UPROPERTY()
	TMap<UPrimitiveComponent*, TEnumAsByte<ECollisionEnabled::Type>> OriginalCollisionSettings;
};
