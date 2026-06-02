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
    if (Actor->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
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

    if (Actor->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
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

    if (Actor->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
    {
        IToggleableInterface::Execute_Disable(Actor);
    }
}

 void UToggleStatics::AddPolicy(AActor* Target, UTogglePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (Target->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
	{
		if (UToggleableComponent* ToggleComp = Cast<UToggleableComponent>(Target->GetComponentByClass(UToggleableComponent::StaticClass())))
		{
			ToggleComp->GetActiveProfile()->AddPolicy(Policy);
		}
	}
}

 void UToggleStatics::AddUniquePolicy(AActor* Target, UTogglePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (Target->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
	{
		if (UToggleableComponent* ToggleComp = Cast<UToggleableComponent>(Target->GetComponentByClass(UToggleableComponent::StaticClass())))
		{
			ToggleComp->GetActiveProfile()->AddUniquePolicy(Policy);
		}
	}
}

 void UToggleStatics::AddPolicies(AActor* Target, const TArray<UTogglePolicy*>& Policies)
{
	if (!Target)
	{
		return;
	}
	if (Target->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
	{
		if (UToggleableComponent* ToggleComp = Cast<UToggleableComponent>(Target->GetComponentByClass(UToggleableComponent::StaticClass())))
		{
			ToggleComp->GetActiveProfile()->AddPolicies(Policies);
		}
	}
}


 void UToggleStatics::RemovePolicy(AActor* Target, UTogglePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (Target->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
	{
		if (UToggleableComponent* ToggleComp = Cast<UToggleableComponent>(Target->GetComponentByClass(UToggleableComponent::StaticClass())))
		{
			ToggleComp->GetActiveProfile()->RemovePolicy(Policy);
		}
	}
}

 void UToggleStatics::RemovePolicies(AActor* Target, const TArray<UTogglePolicy*>& Policies) {
	if (!Target)
	{
		return;
	}
	if (Target->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
	{
		if (UToggleableComponent* ToggleComp = Cast<UToggleableComponent>(Target->GetComponentByClass(UToggleableComponent::StaticClass())))
		{
			ToggleComp->GetActiveProfile()->RemovePolicies(Policies);
		}
	}
}

 void UToggleStatics::ClearPolicies(AActor* Target) {
	if (!Target)
	{
		return;
	}
	if (Target->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
	{
		if (UToggleableComponent* ToggleComp = Cast<UToggleableComponent>(Target->GetComponentByClass(UToggleableComponent::StaticClass())))
		{
			ToggleComp->GetActiveProfile()->ClearPolicies();
		}
	}
}