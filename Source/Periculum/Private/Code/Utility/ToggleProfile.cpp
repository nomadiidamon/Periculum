// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Utility/ToggleProfile.h"

void UToggleProfile::AddPolicy(UTogglePolicy* Policy)
{
	if (!Policy)
	{
		return;
	}
	TogglePolicies.Add(Policy);

	HandleProfileChanged();
}

void UToggleProfile::AddPolicies(const TArray<UTogglePolicy*>& Policies)
{
	TArray<UTogglePolicy*> ValidPolicies;
	for (UTogglePolicy* Policy : Policies)
	{
		if (Policy)
		{
			ValidPolicies.Add(Policy);
		}
	}
	TogglePolicies.Append(ValidPolicies);
	HandleProfileChanged();
}

void UToggleProfile::AddUniquePolicy(UTogglePolicy* Policy)
{
	TogglePolicies.AddUnique(Policy);

	HandleProfileChanged();
}

void UToggleProfile::AddUniquePolicies(const TArray<UTogglePolicy*>& Policies)
{
	TArray<UTogglePolicy*> ValidPolicies;
	for (UTogglePolicy* Policy : Policies)
	{
		if (Policy)
		{
			ValidPolicies.Add(Policy);
		}
	}
	TogglePolicies.Append(ValidPolicies);

	HandleProfileChanged();
}

void UToggleProfile::RemovePolicy(UTogglePolicy* Policy)
{
	TogglePolicies.Remove(Policy);
	HandleProfileChanged();
}

void UToggleProfile::RemovePolicies(const TArray<UTogglePolicy*>& Policies)
{
	for (UTogglePolicy* Policy : Policies)
	{
		RemovePolicy(Policy);
	}
	HandleProfileChanged();
}

void UToggleProfile::ClearPolicies()
{
	TogglePolicies.Empty();
	HandleProfileChanged();
}

void UToggleProfile::HandleProfileChanged()
{
	if (OnProfileChanged.IsBound())
	{
		OnProfileChanged.Broadcast(this);
	}
}
