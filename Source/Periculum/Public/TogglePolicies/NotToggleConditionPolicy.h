// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "TogglePolicies/ConditionalTogglePolicy.h"
#include "NotToggleConditionPolicy.generated.h"

/**
 * A toggle policy that negates the condition of another toggle policy.
 */
UCLASS()
class PERICULUM_API UNotToggleConditionPolicy : public UTogglePolicy
{
	GENERATED_BODY()

public:
	/// <summary>
	/// The condition that will be negated. If the condition evaluates to true, this policy will evaluate to false, and vice versa.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NotToggleConditionPolicy")
	TObjectPtr<UConditionalTogglePolicy> Condition;	
};
