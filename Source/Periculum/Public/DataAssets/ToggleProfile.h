// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TogglePolicies/TogglePolicy.h"
#include "ToggleProfile.generated.h"

class UTogglePolicy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToggleProfileChanged, UToggleProfile*, NewProfile);

/**
 * A data asset that holds a collection of toggle policies. 
 * It allows adding, removing, and managing toggle policies, and notifies listeners when the profile changes.
 */


UCLASS(BlueprintType)
class PERICULUM_API UToggleProfile : public UDataAsset
{
	GENERATED_BODY()

public:
	/// <summary>
	/// The array of toggle policies associated with this profile. Each policy defines specific rules or conditions for toggling features on or off.
	/// </summary>
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "ToggleProfile")
	TArray<UTogglePolicy*> TogglePolicies;

public:
	/// <summary>
	/// A multicast delegate that is triggered whenever the toggle profile changes. Listeners can subscribe to this event to be notified of changes in the profile.
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "ToggleProfile")
	FOnToggleProfileChanged OnProfileChanged;

private:
	/// <summary>
	/// UBlueprintFunctionLibrary class that is declared as a friend to allow access to private members of UToggleProfile. 
	/// This enables the static functions in UToggleStatics to manipulate toggle profiles directly.
	/// </summary>
	friend class UToggleStatics;

private:
	/// <summary>
	/// Adds a new toggle policy to the profile. If the policy is valid (not null), it is added to the TogglePolicies array, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policy">The toggle policy to add.</param>
	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void AddPolicy(UTogglePolicy* Policy);

	/// <summary>
	/// Adds an array of toggle policies to the profile. Each valid policy in the array is added to the TogglePolicies array, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policies">The array of toggle policies to add.</param>
	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void AddPolicies(const TArray<UTogglePolicy*>& Policies);

	/// <summary>
	/// Adds a unique toggle policy to the profile. If the policy is not already present in the TogglePolicies array, it is added, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policy">The toggle policy to add.</param>
	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void AddUniquePolicy(UTogglePolicy* Policy);
	
	/// <summary>
	/// Adds an array of unique toggle policies to the profile. Each policy that is not already present in the TogglePolicies array is added, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policies">The array of toggle policies to add.</param>	
	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void AddUniquePolicies(const TArray<UTogglePolicy*>& Policies);

	/// <summary>
	/// Removes a toggle policy from the profile. If the policy is present in the TogglePolicies array, it is removed, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policy">The toggle policy to remove.</param>
	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void RemovePolicy(UTogglePolicy* Policy);

	/// <summary>
	/// Removes an array of toggle policies from the profile. Each policy that is present in the TogglePolicies array is removed, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policies">The array of toggle policies to remove.</param>
	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void RemovePolicies(const TArray<UTogglePolicy*>& Policies);

	/// <summary>
	/// Clears all toggle policies from the profile. The TogglePolicies array is emptied, and the profile change event is triggered.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "ToggleProfile")
	void ClearPolicies();

	/// <summary>
	/// Handler function that is called whenever the toggle profile changes. It broadcasts the OnProfileChanged event to notify any listeners of the change.
	/// </summary>
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
