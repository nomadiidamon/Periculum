// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TracePolicies/TracePolicy.h"
#include "SphereTracePolicy.generated.h"

/**
 * Performs a sphere sweep from the owning actor, using local-space start/end offsets.
 */
UCLASS(EditInlineNew)
class PERICULUM_API USphereTracePolicy : public UTracePolicy
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	FVector StartOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	FVector EndOffset = FVector(100.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy", meta = (ClampMin = "0.0"))
	float Radius = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	bool bMultiTrace = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	bool bDrawDebug = false;

	virtual FTracePolicyResult Apply_Implementation(UObject* Target) const override;
};
