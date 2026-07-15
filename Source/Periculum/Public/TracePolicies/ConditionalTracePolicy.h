// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TracePolicies/TracePolicy.h"
#include "ConditionalTracePolicy.generated.h"

/**
 * Abstract base for trace policies that gate execution behind a boolean condition.
 * Subclass this to define a concrete condition; the CanApply check delegates to Evaluate.
 * Mirrors UConditionalTogglePolicy.
 */
UCLASS(Abstract, EditInlineNew)
class PERICULUM_API UConditionalTracePolicy : public UTracePolicy
{
	GENERATED_BODY()

public:
	/// <summary>
	/// Checks whether this policy can be applied to the given target.
	/// </summary>
	/// <param name="Target">The target object to evaluate.</param>
	/// <returns>True if the policy can be applied, false otherwise.</returns>
	UFUNCTION(BlueprintNativeEvent)
	bool Evaluate(UObject* Target) const;

	virtual bool CanApply_Implementation(UObject* Target) const override;
};

