// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TogglePolicy.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPolicyStackPriority : uint8
{
	Low = 0 UMETA(DisplayName = "Low"),
	Standard = 25 UMETA(DisplayName = "Standard"),
	Medium = 50 UMETA(DisplayName = "Medium"),
	High = 75 UMETA(DisplayName = "High"),
	Extreme = 100 UMETA(DisplayName = "Extreme")
};



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
	bool CanApply(UObject* Target, bool& bEnable);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TogglePolicy")
	void Apply(UObject* Target, bool& bEnable);

public:
	// Overload the less-than operator to compare policies based on their stack priority and scalar
	bool operator<(const UTogglePolicy& Other) const
	{
		int32 ThisPriority = static_cast<int32>(PolicyStackPriority) + PriorityScalar;
		int32 OtherPriority = static_cast<int32>(Other.PolicyStackPriority) + Other.PriorityScalar;
		return ThisPriority < OtherPriority;
	}

	// Overload the greater-than operator to compare policies based on their stack priority and scalar
	bool operator>(const UTogglePolicy& Other) const
	{
		int32 ThisPriority = static_cast<int32>(PolicyStackPriority) + PriorityScalar;
		int32 OtherPriority = static_cast<int32>(Other.PolicyStackPriority) + Other.PriorityScalar;
		return ThisPriority > OtherPriority;
	}

	// Overload the equality operator to compare policies based on their stack priority and scalar
	bool operator==(const UTogglePolicy& Other) const
	{
		int32 ThisPriority = static_cast<int32>(PolicyStackPriority) + PriorityScalar;
		int32 OtherPriority = static_cast<int32>(Other.PolicyStackPriority) + Other.PriorityScalar;
		return ThisPriority == OtherPriority;
	}

	// Overload the inequality operator to compare policies based on their stack priority and scalar
	bool operator!=(const UTogglePolicy& Other) const
	{
		return !(*this == Other);
	}

};
