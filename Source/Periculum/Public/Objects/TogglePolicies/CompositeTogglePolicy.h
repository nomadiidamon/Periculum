// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TogglePolicies/TogglePolicy.h"
#include "CompositeTogglePolicy.generated.h"

/**
 * 
 */
UCLASS()
class PERICULUM_API UCompositeTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "CompositeTogglePolicy")
	TArray<UTogglePolicy*> SubPolicies;
	
};
