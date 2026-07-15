// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TracePolicies/TracePolicy.h"
#include "SphereTracePolicy.generated.h"

/**
 * Performs a sphere sweep from the owning actor, using local-space start/end offsets.
 */
UCLASS(EditInlineNew)
class PERICULUM_API USphereTracePolicy : public UTracePolicy
{
	GENERATED_BODY()

public:
	/// <summary>
	/// The local-space offset from the actor's location to begin the sphere trace. This defines the starting point of the sweep in relation to the actor's position.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	FVector StartOffset = FVector::ZeroVector;

	/// <summary>
	/// The local-space offset from the actor's location to end the sphere trace. This defines the ending point of the sweep in relation to the actor's position.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	FVector EndOffset = FVector(100.0f, 0.0f, 0.0f);

	/// <summary>
	/// The radius of the sphere used in the trace. This determines the size of the sphere that will be swept along the path defined by StartOffset and EndOffset.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy", meta = (ClampMin = "0.0"))
	float Radius = 25.0f;

	/// <summary>
	/// The collision channel to use for the sphere trace. This defines what types of objects the trace will interact with, based on their collision settings.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	/// <summary>
	/// Whether to trace against complex collision. If true, the trace will consider the detailed geometry of objects; if false, it will use simplified collision shapes.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	bool bMultiTrace = false;

	/// <summary>
	/// Whether to draw debug lines for the sphere trace. If true, visual debug information will be rendered in the game world to show the path and results of the trace.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	bool bDrawDebug = false;

	virtual FTracePolicyResult Apply_Implementation(UObject* Target) const override;
};
