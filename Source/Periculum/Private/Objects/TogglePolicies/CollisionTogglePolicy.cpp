// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TogglePolicies/CollisionTogglePolicy.h"

void UCollisionTogglePolicy::Apply_Implementation(UObject* Target, bool bEnable)
{
	AActor* Actor = Cast<AActor>(Target);
	if (!Actor)
	{
		return;
	}

	TArray<UPrimitiveComponent*> Components;
	Actor->GetComponents<UPrimitiveComponent>(Components);

	if (bEnable) {

		for (UPrimitiveComponent* Primitive : Components)
		{
			if (!Primitive)
			{
				continue;
			}
			if (const TEnumAsByte<ECollisionEnabled::Type>* Saved = OriginalCollisionSettings.Find(Primitive))
			{
				Primitive->SetCollisionEnabled(Saved->GetValue());
			}

		}
		OriginalCollisionSettings.Empty();
	}
	else {
		ECollisionEnabled::Type TargetMode = ECollisionEnabled::NoCollision;
		switch (DisableMode)
		{
		case ECollisionToggleMode::QueryOnly:
			TargetMode = ECollisionEnabled::QueryOnly;
			break;

		case ECollisionToggleMode::PhysicsOnly:
			TargetMode = ECollisionEnabled::PhysicsOnly;
			break;

		case ECollisionToggleMode::QueryAndPhysics:
			TargetMode = ECollisionEnabled::QueryAndPhysics;
			break;

		default:
			break;

		}

		for (UPrimitiveComponent* Primitive : Components)
		{
			if (!Primitive)
			{
				continue;
			}
			OriginalCollisionSettings.Add(Primitive, Primitive->GetCollisionEnabled());
			Primitive->SetCollisionEnabled(TargetMode);
		}
	}

#if WITH_EDITOR
	FString CollisionModeString;
	switch (DisableMode)
	{
		case ECollisionToggleMode::NoCollision:
			CollisionModeString = TEXT("No Collision");
			break;
		case ECollisionToggleMode::QueryOnly:
			CollisionModeString = TEXT("Query Only");
			break;
		case ECollisionToggleMode::PhysicsOnly:
			CollisionModeString = TEXT("Physics Only");
			break;
		case ECollisionToggleMode::QueryAndPhysics:
			CollisionModeString = TEXT("Query and Physics");
			break;
		default:
			CollisionModeString = TEXT("Unknown");
			break;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Actor %s collision set to %s"), *Actor->GetName(), bEnable ? TEXT("Enabled") : TEXT("Disabled")));	
#endif

}
