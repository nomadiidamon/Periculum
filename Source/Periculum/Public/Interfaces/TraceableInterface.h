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
 * This interface defines the contract for objects that can perform traces in the Periculum system. Implementing this interface allows an object to participate in trace operations
 */
class PERICULUM_API ITraceableInterface
{
	GENERATED_BODY()

public:
	/// <summary>
	/// Executes the full trace policy stack (Profile + RuntimePolicies) and returns the aggregate result.
	/// </summary>
	/// <returns>The aggregate trace result.</returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTraceResult PerformTrace();

	/// <summary>
	/// Returns the result of the most recently executed trace without re-running it.
	/// </summary>
	/// <returns>The result of the last trace.</returns>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTraceResult GetLastTraceResult() const;
};
