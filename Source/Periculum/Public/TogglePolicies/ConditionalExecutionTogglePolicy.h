// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "TogglePolicies/ConditionalTogglePolicy.h"
#include "ConditionalExecutionTogglePolicy.generated.h"

/**
 * A toggle policy that applies another toggle policy based on a condition. If the condition is met, the specified policy will be applied to the target object.
 */
UCLASS(EditInlineNew)
class PERICULUM_API UConditionalExecutionTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()

public:
	/// <summary>
	/// The condition that determines whether the specified policy should be applied. This should be an instance of a class derived from UConditionalTogglePolicy, which implements the logic to evaluate the condition.
	/// </summary>
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "TogglePolicy")
	TObjectPtr<UConditionalTogglePolicy> Condition;

	/// <summary>
	/// The policy that will be applied if the condition is met.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TogglePolicy")
	TObjectPtr<UTogglePolicy> PolicyToApply;

	virtual bool CanApply_Implementation(UObject* Target, bool bEnable) override;

	virtual void Apply_Implementation(UObject* Target, bool bEnable) override;

};
