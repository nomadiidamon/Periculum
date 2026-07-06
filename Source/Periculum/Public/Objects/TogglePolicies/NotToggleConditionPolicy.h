// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TogglePolicies/TogglePolicy.h"
#include "Objects/TogglePolicies/ConditionalTogglePolicy.h"
#include "NotToggleConditionPolicy.generated.h"

/**
 * 
 */
UCLASS()
class PERICULUM_API UNotToggleConditionPolicy : public UTogglePolicy
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NotToggleConditionPolicy")
	TObjectPtr<UConditionalTogglePolicy> Condition;	
};
