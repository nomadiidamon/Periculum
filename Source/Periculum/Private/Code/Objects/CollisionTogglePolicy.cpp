// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Objects/CollisionTogglePolicy.h"

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
}
