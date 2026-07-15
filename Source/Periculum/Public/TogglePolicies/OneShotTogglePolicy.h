// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "OneShotTogglePolicy.generated.h"

/**
 * Enum to specify when the one-shot toggle policy should trigger.
 */ 
UENUM(BlueprintType)
enum class EOneShotTriggerOn : uint8
{
    Enable  UMETA(DisplayName = "On Enable"),
    Disable UMETA(DisplayName = "On Disable"),
    Either  UMETA(DisplayName = "Either"),
};

/**
 * A toggle policy that allows a one-time use of a toggle action.
 */
UCLASS()
class PERICULUM_API UOneShotTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	

public:
    /// <summary>
	/// The condition under which the one-shot toggle policy should trigger. This can be set to trigger on enable, disable, or either action.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OneShotTogglePolicy")
    EOneShotTriggerOn TriggerOn = EOneShotTriggerOn::Enable;

    /// <summary>
	/// The maximum number of times the toggle action can be applied. Once this limit is reached, the policy will no longer allow the action to be applied.
	/// When set to 0, the policy will allow unlimited uses.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OneShotTogglePolicy", meta = (ClampMin = "0"))
    int32 MaxUses = 1;

    virtual bool CanApply_Implementation(UObject* Target, bool bEnable) override;
    virtual void Apply_Implementation(UObject* Target, bool bEnable) override;

private:
	/// <summary>
	/// The current count of how many times the toggle action has been applied. This is used to track the number of uses and enforce the maximum limit.
	/// </summary>
	UPROPERTY(VisibleAnywhere, Category = "OneShotTogglePolicy")
    int32 UseCount = 0;

    /// <summary>
	/// Checks whether the current toggle action matches the trigger condition specified in the policy. This is used to determine if the policy should be applied based on the current state of the toggle action (enable or disable).
    /// </summary>
    /// <param name="bEnable">The current state of the toggle action (enable or disable).</param>
    /// <returns>True if the current toggle action matches the trigger condition, false otherwise.</returns>
    bool MatchesTrigger(bool bEnable) const;

    /// <summary>
	/// Returns the remaining number of uses left for this one-shot toggle policy. If MaxUses is set to 0, it indicates unlimited uses, and the function will return -1.
    /// </summary>
    /// <returns>The number of remaining uses, or -1 if unlimited.</returns>
    int32 GetRemainingUses() const
    {
        return MaxUses > 0 ? FMath::Max(0, MaxUses - UseCount) : -1;
	}
};
