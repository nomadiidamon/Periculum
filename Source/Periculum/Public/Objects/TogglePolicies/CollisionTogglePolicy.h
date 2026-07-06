// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TogglePolicies/TogglePolicy.h"
#include "CollisionTogglePolicy.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECollisionToggleMode : uint8
{
	NoCollision UMETA(DisplayName = "No Collision"),
	QueryOnly UMETA(DisplayName = "Query Only"),
	PhysicsOnly UMETA(DisplayName = "Physics Only"),
	QueryAndPhysics UMETA(DisplayName = "Query and Physics"),
};

UCLASS(EditInlineNew)
class PERICULUM_API UCollisionTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CollisionTogglePolicy")
	ECollisionToggleMode DisableMode = ECollisionToggleMode::NoCollision;

	virtual void Apply_Implementation(UObject* Target, bool bEnable) override;

private:
	UPROPERTY()
	TMap<UPrimitiveComponent*, TEnumAsByte<ECollisionEnabled::Type>> OriginalCollisionSettings;
};
