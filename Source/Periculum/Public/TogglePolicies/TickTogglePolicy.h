// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "TickTogglePolicy.generated.h"

/**
 * A toggle policy that controls the ticking behavior of a target object.
 */
UCLASS(EditInlineNew)
class PERICULUM_API UTickTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	
public:
	virtual void Apply_Implementation(UObject* Target, bool bEnable) override;
};
