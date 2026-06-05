// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Utility/ToggleStatics.h"
#include "Code/Interfaces/ToggleableInterface.h"
#include "Code/Utility/ToggleProfile.h"


void UToggleStatics::ToggleActor(AActor* Actor, bool bEnable)
{
    if (!Actor)
    {
        return;
    }
    if (ActorIsToggleable(Actor))
    {
        IToggleableInterface::Execute_SetEnabled(Actor, bEnable);
    }
}

void UToggleStatics::EnableActor(AActor* Actor)
{
    if (!Actor)
    {
        return;
    }

    if (ActorIsToggleable(Actor))
    {
        IToggleableInterface::Execute_Enable(Actor);
    }
}

void UToggleStatics::DisableActor(AActor* Actor)
{
    if (!Actor)
    {
        return;
    }

    if (ActorIsToggleable(Actor))
    {
        IToggleableInterface::Execute_Disable(Actor);
    }
}

UToggleProfile* UToggleStatics::GetToggleProfile(AActor* Target)
{
	if (!Target)
	{
		return nullptr;
	}
	if (UToggleableComponent* ToggleComp = Cast<UToggleableComponent>(Target->GetComponentByClass(UToggleableComponent::StaticClass())))
	{
		return ToggleComp->GetActiveProfile();
	}
	return nullptr;
}

void UToggleStatics::AddPolicy(AActor* Target, UTogglePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (ActorIsToggleable(Target))
	{
		if (UToggleProfile* Profile = GetToggleProfile(Target))
		{
			Profile->AddPolicy(Policy);
		}
	}
}

 void UToggleStatics::AddUniquePolicy(AActor* Target, UTogglePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (ActorIsToggleable(Target))
	{
		if (UToggleProfile* Profile = GetToggleProfile(Target))
		{
			Profile->AddUniquePolicy(Policy);
		}
	}
}

 void UToggleStatics::AddPolicies(AActor* Target, const TArray<UTogglePolicy*>& Policies)
{
	if (!Target)
	{
		return;
	}
	if (ActorIsToggleable(Target))
	{
		if (UToggleProfile* Profile = GetToggleProfile(Target))
		{
			Profile->AddPolicies(Policies);
		}
	}
}


 void UToggleStatics::RemovePolicy(AActor* Target, UTogglePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (ActorIsToggleable(Target))
	{
		if (UToggleProfile* Profile = GetToggleProfile(Target))
		{
			Profile->RemovePolicy(Policy);
		}
	}
}

 void UToggleStatics::RemovePolicies(AActor* Target, const TArray<UTogglePolicy*>& Policies) {
	if (!Target)
	{
		return;
	}
	if (ActorIsToggleable(Target))
	{
		if (UToggleProfile* Profile = GetToggleProfile(Target))
		{
			Profile->RemovePolicies(Policies);
		}
	}
}

 void UToggleStatics::ClearPolicies(AActor* Target) {
	if (!Target)
	{
		return;
	}
	if (ActorIsToggleable(Target))
	{
		if (UToggleProfile* Profile = GetToggleProfile(Target))
		{
			Profile->ClearPolicies();
		}
	}
}

 bool UToggleStatics::ActorIsToggleable(AActor* Target)
 {
	if (!Target)
	{
		return false;
	}
	if (Target->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
	{
		return true;
	}
	return false;
 }
