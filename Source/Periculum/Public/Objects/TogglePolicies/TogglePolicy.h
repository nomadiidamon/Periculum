// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Defines/PolicyDefines.h"
#include "TogglePolicy.generated.h"


UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class PERICULUM_API UTogglePolicy : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TogglePolicy")
	EPolicyStackPriority PolicyStackPriority = EPolicyStackPriority::Standard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TogglePolicy", meta=(ClampMin="0", ClampMax="100"))
	int32 PriorityScalar = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TogglePolicy")
	bool CanApply(UObject* Target, bool bEnable);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TogglePolicy")
	void Apply(UObject* Target, bool bEnable);

public:
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
