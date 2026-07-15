// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "CompositeTogglePolicy.generated.h"

/**
 * A toggle policy that applies multiple sub-policies in sequence. This allows for complex toggling behavior by combining simpler policies.
 */
UCLASS()
class PERICULUM_API UCompositeTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()

public:
	/// <summary>
	/// The list of sub-policies that will be applied in sequence. Each sub-policy will be applied to the target object when this composite policy is applied.
	/// </summary>
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "CompositeTogglePolicy")
	TArray<UTogglePolicy*> SubPolicies;
	
};
