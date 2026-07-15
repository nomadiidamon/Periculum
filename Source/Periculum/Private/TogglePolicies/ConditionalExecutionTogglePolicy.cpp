// Fill out your copyright notice in the Description page of Project Settings.


#include "TogglePolicies/ConditionalExecutionTogglePolicy.h"

bool UConditionalExecutionTogglePolicy::CanApply_Implementation(UObject* Target, bool bEnable)
{
	if (!Condition || !PolicyToApply)
	{
		return false;
	}
	if (!Condition->Evaluate(Target, bEnable))
	{
		return false;
	}
	return PolicyToApply->CanApply(Target, bEnable);
}

void UConditionalExecutionTogglePolicy::Apply_Implementation(UObject* Target, bool bEnable)
{
	if (!Condition || !PolicyToApply)
	{
		return;
	}
	if (Condition->Evaluate(Target, bEnable))
	{
		PolicyToApply->Apply(Target, bEnable);
	}
}
