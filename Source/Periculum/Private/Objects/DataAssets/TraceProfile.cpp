// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/DataAssets/TraceProfile.h"

void UTraceProfile::AddPolicy(UTracePolicy* Policy)
{
	if (!Policy) { return; }
	TracePolicies.Add(Policy);
	HandleProfileChanged();
}

void UTraceProfile::AddPolicies(const TArray<UTracePolicy*>& Policies)
{
	for (UTracePolicy* Policy : Policies)
	{
		if (Policy) { TracePolicies.Add(Policy); }
	}
	HandleProfileChanged();
}

void UTraceProfile::AddUniquePolicy(UTracePolicy* Policy)
{
	TracePolicies.AddUnique(Policy);
	HandleProfileChanged();
}

void UTraceProfile::AddUniquePolicies(const TArray<UTracePolicy*>& Policies)
{
	for (UTracePolicy* Policy : Policies)
	{
		if (Policy) { TracePolicies.AddUnique(Policy); }
	}
	HandleProfileChanged();
}

void UTraceProfile::RemovePolicy(UTracePolicy* Policy)
{
	TracePolicies.Remove(Policy);
	HandleProfileChanged();
}

void UTraceProfile::RemovePolicies(const TArray<UTracePolicy*>& Policies)
{
	for (UTracePolicy* Policy : Policies)
	{
		TracePolicies.Remove(Policy);
	}
	HandleProfileChanged();
}

void UTraceProfile::ClearPolicies()
{
	TracePolicies.Empty();
	HandleProfileChanged();
}

void UTraceProfile::HandleProfileChanged()
{
	if (OnProfileChanged.IsBound())
	{
		OnProfileChanged.Broadcast(this);
	}
}