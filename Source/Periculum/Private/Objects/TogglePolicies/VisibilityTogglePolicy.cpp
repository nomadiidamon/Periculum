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

        if (bPropagateToChildren)
        {
            TArray<AActor*> AttachedActors;
            Actor->GetAttachedActors(AttachedActors);
            for (AActor* ChildActor : AttachedActors)
            {
                if (ChildActor)
                {
                    ChildActor->SetActorHiddenInGame(bEnable);
                }
            }
		}

#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Actor %s visibility set to %s"), *Actor->GetName(), bEnable ? TEXT("Hidden") : TEXT("Visible")));
#endif
    }
}
