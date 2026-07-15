// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "VisibilityTogglePolicy.generated.h"

/**
 * A toggle policy that controls the visibility of a target object.
 */
UCLASS(EditInlineNew)
class PERICULUM_API UVisibilityTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()

public:
	/// <summary>
	/// Whether to propagate the visibility change to child objects. If true, child objects will also have their visibility changed when this policy is applied.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VisibilityTogglePolicy")
	bool bPropagateToChildren = true;

	virtual void Apply_Implementation(UObject* Target, bool bEnable) override;	
};
