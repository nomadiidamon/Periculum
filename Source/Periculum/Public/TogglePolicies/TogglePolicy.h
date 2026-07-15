// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/PolicyDefines.h"
#include "TogglePolicy.generated.h"

/**
 * An abstract base class for toggle policies that can be applied to objects. 
 Toggle policies define how an object should behave when it is enabled or disabled, and can be used to implement various behaviors such as changing material parameters, modifying collision settings, or executing custom logic.
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class PERICULUM_API UTogglePolicy : public UObject
{
	GENERATED_BODY()

public:
	/// <summary>
	/// The priority of this policy in the stack. Policies with higher priority will be applied before those with lower priority. 
	/// This allows for more granular control over the order in which policies are applied, especially when multiple policies are present.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TogglePolicy")
	EPolicyStackPriority PolicyStackPriority = EPolicyStackPriority::Standard;

	/// <summary>
	/// An additional scalar value that can be used to further adjust the effective priority of this policy.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TogglePolicy", meta=(ClampMin="0", ClampMax="100"))
	int32 PriorityScalar = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TogglePolicy")
	bool CanApply(UObject* Target, bool bEnable);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TogglePolicy")
	void Apply(UObject* Target, bool bEnable);

public:
	/// <summary>
	/// Returns the effective priority of this policy, which is the sum of the stack priority and the priority scalar.
	/// </summary>
	/// <returns>The effective priority of this policy.</returns>
	int32 GetEffectivePriority() const
	{
		return static_cast<int32>(PolicyStackPriority) + PriorityScalar;
	}

	// Overload the less-than operator to compare policies based on their stack priority and scalar
	bool operator<(const UTogglePolicy& Other) const
	{
		int32 ThisPriority = GetEffectivePriority();
		int32 OtherPriority = Other.GetEffectivePriority();
		return ThisPriority < OtherPriority;
	}

	// Overload the greater-than operator to compare policies based on their stack priority and scalar
	bool operator>(const UTogglePolicy& Other) const
	{
		int32 ThisPriority = GetEffectivePriority();
		int32 OtherPriority = Other.GetEffectivePriority();
		return ThisPriority > OtherPriority;
	}

	// Overload the equality operator to compare policies 
	bool operator==(const UTogglePolicy& Other) const
	{
		return this == &Other;
	}

	// Overload the inequality operator to compare policies
	bool operator!=(const UTogglePolicy& Other) const
	{
		return !(*this == Other);
	}

};
