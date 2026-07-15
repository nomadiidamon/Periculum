// Fill out your copyright notice in the Description page of Project Settings.


#include "TracePolicies/ConditionalTracePolicy.h"

bool UConditionalTracePolicy::Evaluate_Implementation(UObject* Target) const
{
	return true;
}

bool UConditionalTracePolicy::CanApply_Implementation(UObject* Target) const
{
	return Evaluate(Target);
}