// Fill out your copyright notice in the Description page of Project Settings.


#include "TracePolicies/TracePolicy.h"

bool UTracePolicy::CanApply_Implementation(UObject* Target) const
{
	return true;
}

FTracePolicyResult UTracePolicy::Apply_Implementation(UObject* Target) const
{
	FTracePolicyResult Result;
	Result.PolicyTag = PolicyTag;

	if (OnTracePolicyCompleted.IsBound())
	{
		OnTracePolicyCompleted.Broadcast(Result);
	}

	return Result;
}