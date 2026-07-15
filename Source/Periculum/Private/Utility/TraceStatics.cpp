// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/TraceStatics.h"
#include "ActorComponents/TraceComponent.h"

FTraceResult UTraceStatics::PerformTrace(AActor* Target)
{
	if (!Target)
	{
		return FTraceResult();
	}
	if (UTraceComponent* TraceComp = Cast<UTraceComponent>(Target->GetComponentByClass(UTraceComponent::StaticClass())))
	{
		return TraceComp->PerformTrace();
	}
	return FTraceResult();
}

FTracePolicyResult UTraceStatics::PerformTraceByTag(AActor* Target, FName Tag)
{
	if (!Target)
	{
		return FTracePolicyResult();
	}
	if (UTraceComponent* TraceComp = Cast<UTraceComponent>(Target->GetComponentByClass(UTraceComponent::StaticClass())))
	{
		return TraceComp->PerformTraceByTag(Tag);
	}
	return FTracePolicyResult();
}

UTraceProfile* UTraceStatics::GetTraceProfile(AActor* Target)
{
	if (!Target)
	{
		return nullptr;
	}
	if (UTraceComponent* TraceComp = Cast<UTraceComponent>(Target->GetComponentByClass(UTraceComponent::StaticClass())))
	{
		return TraceComp->GetActiveProfile();
	}
	return nullptr;
}

void UTraceStatics::AddPolicy(AActor* Target, UTracePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->AddPolicy(Policy);
		}
	}
}

void UTraceStatics::AddUniquePolicy(AActor* Target, UTracePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->AddUniquePolicy(Policy);
		}
	}
}


void UTraceStatics::AddPolicies(AActor* Target, const TArray<UTracePolicy*>& Policies)
{
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->AddPolicies(Policies);
		}
	}
}

void UTraceStatics::RemovePolicy(AActor* Target, UTracePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->RemovePolicy(Policy);
		}
	}
}

void UTraceStatics::RemovePolicies(AActor* Target, const TArray<UTracePolicy*>& Policies)
{
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->RemovePolicies(Policies);
		}
	}
}

void UTraceStatics::ClearPolicies(AActor* Target)
{
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->ClearPolicies();
		}
	}
}

bool UTraceStatics::ActorIsTraceable(AActor* Target)
{
	if (!Target)
	{
		return false;
	}
	
	return Target->FindComponentByClass<UTraceComponent>() != nullptr;
}