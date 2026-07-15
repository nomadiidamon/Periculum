// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "ConditionalTogglePolicy.generated.h"

/**
 * A policy that evaluates a condition to determine whether a toggle should be applied. This is an abstract class that can be extended to implement specific conditions.
 */
UCLASS(Abstract, EditInlineNew)
class PERICULUM_API UConditionalTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()

public:
	/// <summary>
	/// Runs the condition evaluation logic for the given target and toggle state. This method should be overridden in derived classes to implement specific condition checks.
	/// </summary>
	/// <param name="Target">The target object to evaluate the condition on.</param>
	/// <param name="bEnable">The desired toggle state.</param>
	/// <returns>True if the toggle should be applied, false otherwise.</returns>
	UFUNCTION(BlueprintNativeEvent)
	bool Evaluate(UObject* Target, bool bEnable) const;

	virtual bool CanApply_Implementation(UObject* Target, bool bEnable) override;
	
};
