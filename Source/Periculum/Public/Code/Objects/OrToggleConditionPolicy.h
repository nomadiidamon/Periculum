// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Objects/TogglePolicy.h"
#include "Code/Objects/ConditionalTogglePolicy.h"
#include "OrToggleConditionPolicy.generated.h"

/**
 * 
 */
UCLASS()
class PERICULUM_API UOrToggleConditionPolicy : public UTogglePolicy
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere, Instanced)
	TArray<UConditionalTogglePolicy*> Conditions;
};
