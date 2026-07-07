// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Defines/TraceTypes.h"
#include "TraceableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTraceableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PERICULUM_API ITraceableInterface
{
	GENERATED_BODY()

public:
	// Executes the full trace policy stack (Profile + RuntimePolicies) and returns the aggregate result.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTraceResult PerformTrace();

	// Returns the result of the most recently executed trace without re-running it.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTraceResult GetLastTraceResult() const;
};
