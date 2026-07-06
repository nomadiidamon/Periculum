// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "TraceTypes.generated.h"

/**
 * Result produced by a single UTracePolicy execution.
 */
USTRUCT(BlueprintType)
struct FTracePolicyResult
{
	GENERATED_BODY()

	// Tag copied from the policy that produced this result.
	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	FName PolicyTag = NAME_None;

	// Whether this policy registered at least one hit.
	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	bool bHit = false;

	// All hits gathered (multi-trace aware).
	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	TArray<FHitResult> Hits;
};

/**
 * Aggregate result of running an entire UTraceProfile policy stack.
 */
USTRUCT(BlueprintType)
struct FTraceResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	bool bAnyHit = false;

	UPROPERTY(BlueprintReadOnly, Category = "Trace")
	TArray<FTracePolicyResult> PolicyResults;

	// Returns the first policy result that registered a hit, or nullptr if none did.
	const FTracePolicyResult* GetFirstHit() const
	{
		for (const FTracePolicyResult& Result : PolicyResults)
		{
			if (Result.bHit)
			{
				return &Result;
			}
		}
		return nullptr;
	}

	// Finds the result produced by the policy with the given tag, if any.
	const FTracePolicyResult* FindByTag(FName Tag) const
	{
		return PolicyResults.FindByPredicate([Tag](const FTracePolicyResult& Result)
			{
				return Result.PolicyTag == Tag;
			});
	}
};