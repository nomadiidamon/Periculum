// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Objects/TogglePolicy.h"
#include "ConditionalTogglePolicy.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class PERICULUM_API UConditionalTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()

public:
	virtual bool CanApply_Implementation(UObject* Target, bool& bEnable) override;
	
};
