// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Components/ToggleableComponent.h"
#include "Code/Objects/TogglePolicy.h"
#include "Code/Utility/ToggleProfile.h"


UToggleableComponent::UToggleableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UToggleableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UToggleableComponent::Enable_Implementation()
{
	SetEnabled_Implementation(true);
}

void UToggleableComponent::Disable_Implementation()
{
	SetEnabled_Implementation(false);
}

void UToggleableComponent::SetEnabled_Implementation(bool bNewState)
{
	if (bEnabled == bNewState)
	{
		return;
	}
	bEnabled = bNewState;
	ExecutePolicies(bNewState);
	HandleToggleChange(bNewState);
}

bool UToggleableComponent::IsEnabled_Implementation() const
{
	return bEnabled;
}

void UToggleableComponent::DisableBySource(FName Source)
{
	DisableSources.Add(Source);

	SetEnabled_Implementation(false);
}

void UToggleableComponent::EnableBySource(FName Source)
{
	DisableSources.Remove(Source);

	if (DisableSources.IsEmpty())
	{
		SetEnabled_Implementation(true);
	}
}



void UToggleableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UToggleableComponent::ExecutePolicies(bool bNewState)
{
	TArray<UTogglePolicy*> Policies = BuildPolicyStack();

	Policies.Sort([](const UTogglePolicy& A, const UTogglePolicy& B)
	{
		return A.PolicyStackPriority > B.PolicyStackPriority;
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

TArray<UTogglePolicy*> UToggleableComponent::BuildPolicyStack() const
{
	TArray<UTogglePolicy*> Policies;
	if (Profile)
	{
		Policies.Append(Profile->TogglePolicies);
	}
	Policies.Append(RuntimePolicies);
	return Policies;
}

void UToggleableComponent::HandleToggleChange(bool bNewState)
{
	if (OnToggleChanged.IsBound())
	{
		OnToggleChanged.Broadcast(bNewState);
	}
}
