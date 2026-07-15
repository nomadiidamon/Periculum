// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "TogglePolicies/ConditionalTogglePolicy.h"
#include "OrToggleConditionPolicy.generated.h"

/**
 * A toggle policy that combines multiple conditional policies using a logical OR operation.
 */
UCLASS()
class PERICULUM_API UOrToggleConditionPolicy : public UTogglePolicy
{
	GENERATED_BODY()
	
	/// <summary>
	/// The array of conditional toggle policies that will be evaluated. The policy will be applied if any of the conditions evaluate to true.
	/// </summary>
	UPROPERTY(EditAnywhere, Instanced)
	TArray<UConditionalTogglePolicy*> Conditions;
};
