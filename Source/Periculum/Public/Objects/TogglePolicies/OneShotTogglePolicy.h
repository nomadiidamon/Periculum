// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TogglePolicies/TogglePolicy.h"
#include "OneShotTogglePolicy.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EOneShotTriggerOn : uint8
{
    Enable  UMETA(DisplayName = "On Enable"),
    Disable UMETA(DisplayName = "On Disable"),
    Either  UMETA(DisplayName = "Either"),
};

UCLASS()
class PERICULUM_API UOneShotTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	

public:
    // Which direction of toggle consumes a use
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OneShotTogglePolicy")
    EOneShotTriggerOn TriggerOn = EOneShotTriggerOn::Enable;

    // Total allowed uses before this policy removes itself. 0 = unlimited (acts as normal policy)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OneShotTogglePolicy", meta = (ClampMin = "0"))
    int32 MaxUses = 1;

    virtual bool CanApply_Implementation(UObject* Target, bool bEnable) override;
    virtual void Apply_Implementation(UObject* Target, bool bEnable) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "OneShotTogglePolicy")
    int32 UseCount = 0;

    bool MatchesTrigger(bool bEnable) const;

    int32 GetRemainingUses() const
    {
        return MaxUses > 0 ? FMath::Max(0, MaxUses - UseCount) : -1;
	}
};
