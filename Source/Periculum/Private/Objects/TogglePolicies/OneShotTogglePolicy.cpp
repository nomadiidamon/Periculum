// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TogglePolicies/OneShotTogglePolicy.h"
#include "Utility/ToggleStatics.h"

bool UOneShotTogglePolicy::CanApply_Implementation(UObject* Target, bool bEnable)
{
    if (!MatchesTrigger(bEnable))
    {
        return false;
    }
    return MaxUses == 0 || UseCount < MaxUses;
}

void UOneShotTogglePolicy::Apply_Implementation(UObject* Target, bool bEnable)
{
    if (!MatchesTrigger(bEnable))
    {
        return;
    }

    ++UseCount;

    if (MaxUses > 0 && UseCount >= MaxUses)
    {
        // Remove self from the owning component's profile
        AActor* Actor = Cast<AActor>(Target);
        if (Actor)
        {
			UToggleStatics::RemovePolicy(Actor, this);
        }
    }
}

bool UOneShotTogglePolicy::MatchesTrigger(bool bEnable) const
{
    switch (TriggerOn)
    {
    case EOneShotTriggerOn::Enable:  return bEnable;
    case EOneShotTriggerOn::Disable: return !bEnable;
    case EOneShotTriggerOn::Either:  return true;
    default:                         return false;
    }
}
