// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Objects/TogglePolicies/TogglePolicy.h"
#include "ToggleProfile.generated.h"

/**
 *
 */

class UTogglePolicy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToggleProfileChanged, UToggleProfile*, NewProfile);

UCLASS(BlueprintType)
class PERICULUM_API UToggleProfile : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "ToggleProfile")
	TArray<UTogglePolicy*> TogglePolicies;

public:
	FOnToggleProfileChanged OnProfileChanged;

private:
	friend class UToggleStatics;

private:
	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void AddPolicy(UTogglePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void AddPolicies(const TArray<UTogglePolicy*>& Policies);

	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void AddUniquePolicy(UTogglePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void AddUniquePolicies(const TArray<UTogglePolicy*>& Policies);

	
	
	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void RemovePolicy(UTogglePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void RemovePolicies(const TArray<UTogglePolicy*>& Policies);

	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void ClearPolicies();


	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void HandleProfileChanged();


public:
	// Equality operators for comparing profiles and policy arrays
	bool operator==(const UToggleProfile& Other) const
	{
		return TogglePolicies == Other.TogglePolicies;
	}

	// Inequality operator
	bool operator!=(const UToggleProfile& Other) const
	{
		return !(*this == Other);
	}

	// Less than operator for comparing profiles based on the number of policies and their scalars
	bool operator<(const UToggleProfile& Other) const
	{
		float ThisPriority = 0.0f;
		float OtherPriority = 0.0f;

		for (UTogglePolicy* Policy : TogglePolicies)
		{
			if (Policy)
			{
				ThisPriority += static_cast<int32>(Policy->PolicyStackPriority) + Policy->PriorityScalar;
			}
		}
		for (UTogglePolicy* Policy : Other.TogglePolicies)
		{
			if (Policy)
			{
				OtherPriority += static_cast<int32>(Policy->PolicyStackPriority) + Policy->PriorityScalar;
			}
		}

		return ThisPriority < OtherPriority;
	}

	// Greater than operator for comparing profiles based on the number of policies and their scalars
	bool operator>(const UToggleProfile& Other) const
	{
		float ThisPriority = 0.0f;
		float OtherPriority = 0.0f;
		for (UTogglePolicy* Policy : TogglePolicies)
		{
			if (Policy)
			{
				ThisPriority += static_cast<int32>(Policy->PolicyStackPriority) + Policy->PriorityScalar;
			}
		}
		for (UTogglePolicy* Policy : Other.TogglePolicies)
		{
			if (Policy)
			{
				OtherPriority += static_cast<int32>(Policy->PolicyStackPriority) + Policy->PriorityScalar;
			}
		}
		return ThisPriority > OtherPriority;
	}

	// Equality operator for comparing with an array of policies
	bool operator==(const TArray<UTogglePolicy*>& OtherPolicies) const
	{
		return TogglePolicies == OtherPolicies;
	}

	// Inequality operator for comparing with an array of policies
	bool operator!=(const TArray<UTogglePolicy*>& OtherPolicies) const
	{
		return !(*this == OtherPolicies);
	}
};
