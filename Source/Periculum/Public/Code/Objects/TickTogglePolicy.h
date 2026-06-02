// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Objects/TogglePolicy.h"
#include "TickTogglePolicy.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew)
class PERICULUM_API UTickTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	
public:
	virtual void Apply_Implementation(UObject* Target, bool& bEnable) override;
};
