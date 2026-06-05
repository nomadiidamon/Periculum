// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Objects/ConditionalTogglePolicy.h"

bool UConditionalTogglePolicy::Evaluate_Implementation(UObject* Target, bool bEnable) const
{
	return false;
}

bool UConditionalTogglePolicy::CanApply_Implementation(UObject* Target, bool bEnable)
{
	return Evaluate_Implementation(Target, bEnable);
}
