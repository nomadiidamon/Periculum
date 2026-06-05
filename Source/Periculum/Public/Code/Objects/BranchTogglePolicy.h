// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Objects/TogglePolicy.h"
#include "Code/Objects/ConditionalTogglePolicy.h"
#include "BranchTogglePolicy.generated.h"

/**
 * 
 */
UCLASS()
class PERICULUM_API UBranchTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	
public:

    UPROPERTY(EditAnywhere, Instanced)
    TObjectPtr<UConditionalTogglePolicy> Condition;

    UPROPERTY(EditAnywhere, Instanced)
    TObjectPtr<UTogglePolicy> TruePolicy;

    UPROPERTY(EditAnywhere, Instanced)
    TObjectPtr<UTogglePolicy> FalsePolicy;
};
