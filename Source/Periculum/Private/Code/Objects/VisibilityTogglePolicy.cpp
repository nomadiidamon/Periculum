// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Objects/VisibilityTogglePolicy.h"

void UVisibilityTogglePolicy::Apply_Implementation(UObject* Target, bool& bEnable)
{
    if (AActor* Actor = Cast<AActor>(Target))
    {
        Actor->SetActorHiddenInGame(!bEnable);
    }
}
