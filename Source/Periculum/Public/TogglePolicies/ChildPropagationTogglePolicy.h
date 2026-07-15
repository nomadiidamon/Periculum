// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "ChildPropagationTogglePolicy.generated.h"

/**
 * A toggle policy that applies the toggle to all child objects of the target object, optionally recursively.
 */
UCLASS(EditInlinenew)
class PERICULUM_API UChildPropagationTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	
public:
	/// <summary>
	/// Whether to apply the toggle recursively to all descendants of the target object. If false, only direct children will be affected.
	/// </summary>
	UPROPERTY(EditAnywhere)
	bool bRecursive = true;

	virtual void Apply_Implementation(UObject* Target, bool bEnable) override;
};
