// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TogglePolicies/VisibilityTogglePolicy.h"

void UVisibilityTogglePolicy::Apply_Implementation(UObject* Target, bool bEnable)
{
    if (AActor* Actor = Cast<AActor>(Target))
    {
        if (!Actor)
        {
            return;
		}
        Actor->SetActorHiddenInGame(bEnable);

    }
}
