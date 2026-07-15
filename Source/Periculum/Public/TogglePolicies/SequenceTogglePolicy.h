// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/CompositeTogglePolicy.h"
#include "SequenceTogglePolicy.generated.h"

/**
 * A toggle policy that applies its sub-policies in sequence.
 */
UCLASS()
class PERICULUM_API USequenceTogglePolicy : public UCompositeTogglePolicy
{
	GENERATED_BODY()

public:
	virtual void Apply_Implementation(UObject* Target, bool bEnable) override
	{
		for (UTogglePolicy* Policy : SubPolicies)
		{
			if (!Policy)
			{
				continue;
			}
			if (!Policy->CanApply(Target, bEnable))
			{
				continue;
			}

			Policy->Apply(Target, bEnable);
		}
	}

};
