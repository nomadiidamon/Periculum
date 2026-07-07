// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TracePolicies/TracePolicy.h"
#include "LineTracePolicy.generated.h"

/**
 * Performs a line trace from the owning actor, using local-space start/end offsets.
 */
UCLASS(EditInlineNew)
class PERICULUM_API ULineTracePolicy : public UTracePolicy
{
	GENERATED_BODY()

public:
	// Local-space offset from the actor's location to begin the trace.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	FVector StartOffset = FVector::ZeroVector;

	// Local-space offset from the actor's location to end the trace.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	FVector EndOffset = FVector(100.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	bool bTraceComplex = false;

	// If true, gathers all overlapping hits along the line instead of stopping at the first.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	bool bMultiTrace = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	bool bDrawDebug = false;

	virtual FTracePolicyResult Apply_Implementation(UObject* Target) const override;
};