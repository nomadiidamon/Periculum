// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "TogglePolicies/ConditionalTogglePolicy.h"
#include "AndToggleConditionPolicy.generated.h"

/**
 * A toggle policy that evaluates multiple conditional toggle policies and returns true if all of them are true.
 */
UCLASS()
class PERICULUM_API UAndToggleConditionPolicy : public UTogglePolicy
{
	GENERATED_BODY()

public:
	/// <summary>
	/// The list of conditional toggle policies that will be evaluated. The toggle will only be applied if all conditions return true.
	/// </summary>
	UPROPERTY(EditAnywhere, Instanced)
	TArray<UConditionalTogglePolicy*> Conditions;
	
};
