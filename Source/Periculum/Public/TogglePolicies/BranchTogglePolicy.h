// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "TogglePolicies/ConditionalTogglePolicy.h"
#include "BranchTogglePolicy.generated.h"

/**
 * A toggle policy that branches based on a condition. If the condition is true, the TruePolicy is used; otherwise, the FalsePolicy is used.
 */
UCLASS()
class PERICULUM_API UBranchTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	
public:
    /// <summary>
	/// The condition that determines which policy to use. If the condition evaluates to true, the TruePolicy is applied; otherwise, the FalsePolicy is applied.
    /// </summary>
    UPROPERTY(EditAnywhere, Instanced)
    TObjectPtr<UConditionalTogglePolicy> Condition;

    /// <summary>
	/// The policy to apply if the condition evaluates to true. This policy will be applied to the target object when the toggle is enabled.
    /// </summary>
    UPROPERTY(EditAnywhere, Instanced)
    TObjectPtr<UTogglePolicy> TruePolicy;

    /// <summary>
	/// The policy to apply if the condition evaluates to false. This policy will be applied to the target object when the toggle is disabled.
    /// </summary>
    UPROPERTY(EditAnywhere, Instanced)
    TObjectPtr<UTogglePolicy> FalsePolicy;
};
