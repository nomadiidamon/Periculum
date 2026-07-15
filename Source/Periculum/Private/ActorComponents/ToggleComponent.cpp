// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/ToggleComponent.h"
#include "TogglePolicies/TogglePolicy.h"
#include "DataAssets/ToggleProfile.h"


UToggleComponent::UToggleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UToggleComponent::Enable_Implementation()
{
	SetEnabled_Implementation(true);
}

void UToggleComponent::Disable_Implementation()
{
	SetEnabled_Implementation(false);
}

void UToggleComponent::SetEnabled_Implementation(bool bNewState)
{
	if (bEnabled == bNewState)
	{
		return;
	}
	bEnabled = bNewState;
	ExecutePolicies(bNewState);
	HandleToggleChange(bNewState);
}

bool UToggleComponent::IsEnabled_Implementation() const
{
	return bEnabled;
}

void UToggleComponent::DisableBySource(FName Source)
{
	DisableSources.Add(Source);

	SetEnabled_Implementation(false);
}

void UToggleComponent::EnableBySource(FName Source)
{
	DisableSources.Remove(Source);

	if (DisableSources.IsEmpty())
	{
		SetEnabled_Implementation(true);
	}
}



void UToggleComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UToggleComponent::ExecutePolicies(bool bNewState)
{
	TArray<UTogglePolicy*> Policies = BuildPolicyStack();

	Policies.Sort([](const UTogglePolicy& A, const UTogglePolicy& B)
	{
		return A.GetEffectivePriority() > B.GetEffectivePriority();
		});

	UObject* OwnerObject = GetOwner();

	for (UTogglePolicy* Policy : Policies)
	{
		if (!Policy)
		{
			continue;
		}

		if (!Policy->CanApply(OwnerObject, bNewState))
		{
			continue;
		}

		Policy->Apply(OwnerObject, bNewState);
	}
}

TArray<UTogglePolicy*> UToggleComponent::BuildPolicyStack() const
{
	TArray<UTogglePolicy*> Policies;
	if (Profile)
	{
		Policies.Append(Profile->TogglePolicies);
	}
	Policies.Append(RuntimePolicies);
	return Policies;
}

void UToggleComponent::HandleToggleChange(bool bNewState)
{
	if (OnToggleChanged.IsBound())
	{
		OnToggleChanged.Broadcast(bNewState);
	}
}
