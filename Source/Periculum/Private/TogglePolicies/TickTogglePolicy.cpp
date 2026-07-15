// Fill out your copyright notice in the Description page of Project Settings.


#include "TogglePolicies/TickTogglePolicy.h"

void UTickTogglePolicy::Apply_Implementation(UObject* Target, bool bEnable)
{
	if (UActorComponent* Component = Cast<UActorComponent>(Target))
	{
		Component->SetComponentTickEnabled(bEnable);

#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Component %s tick enabled set to %s"), *Component->GetName(), bEnable ? TEXT("Enabled") : TEXT("Disabled")));
#endif
	}
}
