// Fill out your copyright notice in the Description page of Project Settings.


#include "TogglePolicies/VisibilityTogglePolicy.h"

void UVisibilityTogglePolicy::Apply_Implementation(UObject* Target, bool bEnable)
{
    if (AActor* Actor = Cast<AActor>(Target))
    {
        const bool bShouldHide = !bEnable;
        Actor->SetActorHiddenInGame(bShouldHide);

        if (bPropagateToChildren)
        {
            TArray<AActor*> AttachedActors;
            Actor->GetAttachedActors(AttachedActors);

            for (AActor* ChildActor : AttachedActors)
            {
                if (ChildActor)
                {
                    ChildActor->SetActorHiddenInGame(bShouldHide);
                }
            }
		}

#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Actor %s visibility set to %s"), *Actor->GetName(), bShouldHide ? TEXT("Hidden") : TEXT("Visible")));
#endif
    }
}
