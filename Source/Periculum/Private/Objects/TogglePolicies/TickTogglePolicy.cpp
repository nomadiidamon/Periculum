// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TogglePolicies/TickTogglePolicy.h"

void UTickTogglePolicy::Apply_Implementation(UObject* Target, bool bEnable)
{
	if (UActorComponent* Component = Cast<UActorComponent>(Target))
	{
		Component->SetComponentTickEnabled(bEnable);
	}
}
