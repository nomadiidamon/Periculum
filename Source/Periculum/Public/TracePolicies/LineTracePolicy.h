// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TracePolicies/TracePolicy.h"
#include "LineTracePolicy.generated.h"

/**
 * Performs a line trace from the owning actor, using local-space start/end offsets.
 */
UCLASS(EditInlineNew)
class PERICULUM_API ULineTracePolicy : public UTracePolicy
{
	GENERATED_BODY()

public:
	/// <summary>
	/// The local-space offset from the actor's location to start the trace. This allows for tracing from a point other than the actor's origin, such as a specific socket or component location.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	FVector StartOffset = FVector::ZeroVector;

	/// <summary>
	/// The local-space offset from the actor's location to end the trace. This allows for tracing to a point other than the actor's origin, such as a specific socket or component location.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	FVector EndOffset = FVector(100.0f, 0.0f, 0.0f);

	/// <summary>
	/// The collision channel to use for the line trace. This determines what types of objects the trace will interact with, such as visibility, camera, or custom channels defined in the project settings.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	/// <summary>
	/// Whether to trace against complex collision (triangles) or simple collision (primitives). Complex collision is more accurate but can be more expensive, while simple collision is faster but less precise.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	bool bTraceComplex = false;

	/// <summary>
	/// Whether to perform a multi-trace (returning all hits along the line) or a single trace (returning only the first hit).
	/// Multi-trace can be useful for detecting multiple objects along a path, while single trace is faster and sufficient for many use cases.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	bool bMultiTrace = false;

	/// <summary>
	/// Whether to draw debug lines for the trace in the world. This is useful for visualizing the trace during development and debugging, but should be disabled in production for performance reasons.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	bool bDrawDebug = false;

	virtual FTracePolicyResult Apply_Implementation(UObject* Target) const override;
};