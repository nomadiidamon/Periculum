// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Objects/CollisionTogglePolicy.h"

void UCollisionTogglePolicy::Apply_Implementation(UObject* Target, bool& bEnable)
{
	AActor* Actor = Cast<AActor>(Target);

	if (!Actor)
	{
		return;
	}

	TArray<UPrimitiveComponent*> Components;
	Actor->GetComponents<UPrimitiveComponent>(Components);

	for (UPrimitiveComponent* Primitive : Components)
	{
		if (!Primitive)
		{
			continue;
		}

		if (bEnable)
		{
			Primitive->SetCollisionEnabled(
				ECollisionEnabled::QueryAndPhysics);
		}
		else
		{
			switch (DisableMode)
			{
			case ECollisionToggleMode::NoCollision:
			{
				Primitive->SetCollisionEnabled(
					ECollisionEnabled::NoCollision);
				break;
			}

			case ECollisionToggleMode::QueryOnly:
			{
				Primitive->SetCollisionEnabled(
					ECollisionEnabled::QueryOnly);
				break;
			}

			case ECollisionToggleMode::PhysicsOnly:
			{
				Primitive->SetCollisionEnabled(
					ECollisionEnabled::PhysicsOnly);
				break;
			}

			case ECollisionToggleMode::QueryAndPhysics:
			{
				Primitive->SetCollisionEnabled(
					ECollisionEnabled::QueryAndPhysics);
				break;
			}

			case ECollisionToggleMode::CollisionEnabled:
			{
				Primitive->SetCollisionEnabled(
					ECollisionEnabled::QueryAndPhysics);
				break;
			}
			}
		}
	}
}
