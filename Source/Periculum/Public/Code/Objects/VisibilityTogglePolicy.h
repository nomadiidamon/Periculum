// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Objects/TogglePolicy.h"
#include "VisibilityTogglePolicy.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew)
class PERICULUM_API UVisibilityTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()

public:

	virtual void Apply_Implementation(UObject* Target, bool& bEnable) override;	
};
