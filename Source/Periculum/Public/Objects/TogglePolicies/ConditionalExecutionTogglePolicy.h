// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TogglePolicies/TogglePolicy.h"
#include "Objects/TogglePolicies/ConditionalTogglePolicy.h"
#include "ConditionalExecutionTogglePolicy.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew)
class PERICULUM_API UConditionalExecutionTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()

public:
	// The condition that will be evaluated to determine whether the policy should be applied
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "TogglePolicy")
	TObjectPtr<UConditionalTogglePolicy> Condition;
	
	// The policy that will be applied if the condition is met
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TogglePolicy")
	TObjectPtr<UTogglePolicy> PolicyToApply;

	virtual bool CanApply_Implementation(UObject* Target, bool bEnable) override;

	virtual void Apply_Implementation(UObject* Target, bool bEnable) override;

};
