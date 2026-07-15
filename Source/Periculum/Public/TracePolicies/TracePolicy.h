// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Defines/PolicyDefines.h"
#include "Defines/TraceTypes.h"
#include "Interfaces/TraceableInterface.h"
#include "TracePolicy.generated.h"

/**
 * An abstract base class for trace policies. A trace policy defines a single way of performing a trace, and can be combined with other policies to form a stack of trace behaviors.
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class PERICULUM_API UTracePolicy : public UObject, public ITraceableInterface
{
	GENERATED_BODY()

public:
	/// <summary>
	/// Identifier for this policy, used to determine which policies can be combined in a stack. Policies with the same tag are considered to be of the same type and will not be combined.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TracePolicy")
	FName PolicyTag = NAME_None;

	/// <summary>
	/// The priority of this policy in the stack. Policies with higher priority will be executed before those with lower priority. The effective priority is calculated as PolicyStackPriority + PriorityScalar.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TracePolicy")
	EPolicyStackPriority PolicyStackPriority = EPolicyStackPriority::Standard;

	/// <summary>
	/// The scalar value added to the PolicyStackPriority to determine the effective priority of this policy. This allows for fine-tuning the order of execution within the same priority level.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TracePolicy", meta = (ClampMin = "0", ClampMax = "100"))
	int32 PriorityScalar = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TracePolicy")
	bool CanApply(UObject* Target) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TracePolicy")
	FTracePolicyResult Apply(UObject* Target) const;

public:
	/// <summary>
	/// Returns the effective priority of this policy, calculated as PolicyStackPriority + PriorityScalar. This is used to determine the order of execution in a stack of policies.
	/// </summary>
	/// <returns>The effective priority of this policy.</returns>
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
