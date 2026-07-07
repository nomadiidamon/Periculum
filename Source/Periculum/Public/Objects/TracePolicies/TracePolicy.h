// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Defines/PolicyDefines.h"
#include "Defines/TraceTypes.h"
#include "Interfaces/TraceableInterface.h"
#include "TracePolicy.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class PERICULUM_API UTracePolicy : public UObject, public ITraceableInterface
{
	GENERATED_BODY()

public:
	// Identifies this policy's result inside an FTraceResult.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TracePolicy")
	FName PolicyTag = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TracePolicy")
	EPolicyStackPriority PolicyStackPriority = EPolicyStackPriority::Standard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TracePolicy", meta = (ClampMin = "0", ClampMax = "100"))
	int32 PriorityScalar = 0;

	// Whether this policy can run right now (e.g. gated by a condition). Defaults to true.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TracePolicy")
	bool CanApply(UObject* Target) const;

	// Performs the actual trace and returns its result. Override in concrete subclasses.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TracePolicy")
	FTracePolicyResult Apply(UObject* Target) const;

public:
	int32 GetEffectivePriority() const
	{
		return static_cast<int32>(PolicyStackPriority) + PriorityScalar;
	}

	bool operator<(const UTracePolicy& Other) const
	{
		return GetEffectivePriority() < Other.GetEffectivePriority();
	}

	bool operator>(const UTracePolicy& Other) const
	{
		return GetEffectivePriority() > Other.GetEffectivePriority();
	}

	bool operator==(const UTracePolicy& Other) const
	{
		return this == &Other;
	}

	bool operator!=(const UTracePolicy& Other) const
	{
		return !(*this == Other);
	}
};
