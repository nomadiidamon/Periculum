// Fill out your copyright notice in the Description page of Project Settings.

#include "Code/Objects/ChildPropagationTogglePolicy.h"
#include "Code/Interfaces/ToggleableInterface.h"


void UChildPropagationTogglePolicy::Apply_Implementation(UObject* Target, bool bEnable)
{
    AActor* Actor = Cast<AActor>(Target);

    if (!Actor)
    {
        return;
    }

    TArray<AActor*> Children;
    Actor->GetAttachedActors(Children);

    for (AActor* Child : Children)
    {
        if (Child->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
        {
            IToggleableInterface::Execute_SetEnabled(Child,bEnable);
        }

        if (bRecursive)
        {
            TArray<AActor*> GrandChildren;
            Child->GetAttachedActors(GrandChildren);

            for (AActor* GrandChild : GrandChildren)
            {
                if (GrandChild->GetClass()->ImplementsInterface(UToggleableInterface::StaticClass()))
                {
                    IToggleableInterface::Execute_SetEnabled(GrandChild, bEnable);
                }
            }
        }
    }
}
