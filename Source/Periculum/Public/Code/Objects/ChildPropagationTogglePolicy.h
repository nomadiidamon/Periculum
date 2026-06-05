// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Objects/TogglePolicy.h"
#include "ChildPropagationTogglePolicy.generated.h"

/**
 * 
 */
UCLASS(EditInlinenew)
class PERICULUM_API UChildPropagationTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	bool bRecursive = true;

	virtual void Apply_Implementation(UObject* Target, bool bEnable) override;
};
