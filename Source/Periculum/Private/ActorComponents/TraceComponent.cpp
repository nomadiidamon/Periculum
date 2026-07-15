// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/TraceComponent.h"
#include "DataAssets/TraceProfile.h"
#include "TracePolicies/TracePolicy.h"

UTraceComponent::UTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

FTraceResult UTraceComponent::PerformTrace_Implementation()
{
	TArray<UTracePolicy*> Policies = BuildPolicyStack();

	Policies.Sort([](const UTracePolicy& A, const UTracePolicy& B)
		{
			return A.GetEffectivePriority() > B.GetEffectivePriority();
		});

	UObject* OwnerObject = GetOwner();
	FTraceResult Result;

	for (UTracePolicy* Policy : Policies)
	{
		if (!Policy)
		{
			continue;
		}

		if (!Policy->CanApply(OwnerObject))
		{
			continue;
		}

		FTracePolicyResult PolicyResult = Policy->Apply(OwnerObject);
		Result.bAnyHit |= PolicyResult.bHit;
		Result.PolicyResults.Add(PolicyResult);
	}

	LastTraceResult = Result;

	if (OnTraceCompleted.IsBound())
	{
		OnTraceCompleted.Broadcast(Result);
	}

	return Result;
}

FTraceResult UTraceComponent::GetLastTraceResult_Implementation() const
{
	return LastTraceResult;
}

FTracePolicyResult UTraceComponent::PerformTraceByTag(FName Tag)
{
	UObject* OwnerObject = GetOwner();

	for (UTracePolicy* Policy : BuildPolicyStack())
	{
		if (!Policy || Policy->PolicyTag != Tag)
		{
			continue;
		}

		if (!Policy->CanApply(OwnerObject))
		{
			continue;
		}

		return Policy->Apply(OwnerObject);
	}

	FTracePolicyResult EmptyResult;
	EmptyResult.PolicyTag = Tag;
	return EmptyResult;
}

void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(bAutoTrace);
}

void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bAutoTrace)
	{
		return;
	}

	TimeSinceLastTrace += DeltaTime;
	if (TimeSinceLastTrace >= TraceInterval)
	{
		TimeSinceLastTrace = 0.0f;
		PerformTrace_Implementation();
	}
}

TArray<UTracePolicy*> UTraceComponent::BuildPolicyStack() const
{
	TArray<UTracePolicy*> Policies;
	if (Profile)
	{
		Policies.Append(Profile->TracePolicies);
	}
	Policies.Append(RuntimePolicies);
	return Policies;
}