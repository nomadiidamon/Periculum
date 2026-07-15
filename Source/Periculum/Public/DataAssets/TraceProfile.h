// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TracePolicies/TracePolicy.h"
#include "TraceProfile.generated.h"

class UTracePolicy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTraceProfileChanged, UTraceProfile*, NewProfile);

/**
 * A data asset that holds a collection of trace policies.
 * It allows adding, removing, and managing trace policies, and notifies listeners when the profile changes.
 */

UCLASS(BlueprintType)
class PERICULUM_API UTraceProfile : public UDataAsset
{
	GENERATED_BODY()

public:
	/// <summary>
	/// The array of trace policies associated with this profile. Each policy defines specific rules or conditions for tracing.
	/// </summary>
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "TraceProfile")
	TArray<UTracePolicy*> TracePolicies;

public:
	/// <summary>
	/// A dynamic multicast delegate that is triggered whenever the trace profile changes. Listeners can subscribe to this event to be notified of changes in the profile.
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "TraceProfile")
	FOnTraceProfileChanged OnProfileChanged;

private:
	/// <summary>
	/// UBlueprintFunctionLibrary class that is declared as a friend to allow access to private members of UTraceProfile.
	/// </summary>
	friend class UTraceStatics;

private:
	/// <summary>
	/// Adds a new trace policy to the profile. If the policy is valid (not null), it is added to the TracePolicies array, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policy">The trace policy to add.</param>
	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void AddPolicy(UTracePolicy* Policy);

	/// <summary>
	/// Adds an array of trace policies to the profile. Each valid policy in the array is added to the TracePolicies array, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policies">The array of trace policies to add.</param>
	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void AddPolicies(const TArray<UTracePolicy*>& Policies);

	/// <summary>
	/// Adds a unique trace policy to the profile. If the policy is not already present in the TracePolicies array, it is added, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policy">The trace policy to add.</param>
	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void AddUniquePolicy(UTracePolicy* Policy);

	/// <summary>
	/// Adds an array of unique trace policies to the profile. Each policy that is not already present in the TracePolicies array is added, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policies">The array of trace policies to add.</param>
	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void AddUniquePolicies(const TArray<UTracePolicy*>& Policies);

	/// <summary>
	/// Removes a trace policy from the profile. If the policy is present in the TracePolicies array, it is removed, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policy">The trace policy to remove.</param>
	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void RemovePolicy(UTracePolicy* Policy);

	/// <summary>
	/// Removes an array of trace policies from the profile. Each policy that is present in the TracePolicies array is removed, and the profile change event is triggered.
	/// </summary>
	/// <param name="Policies">The array of trace policies to remove.</param>
	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void RemovePolicies(const TArray<UTracePolicy*>& Policies);

	/// <summary>
	/// Clears all trace policies from the profile. The TracePolicies array is emptied, and the profile change event is triggered.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void ClearPolicies();

	/// <summary>
	/// Handler function that is called whenever the trace profile changes. It broadcasts the OnProfileChanged event to notify any listeners of the change.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void HandleProfileChanged();

public:
	bool operator==(const UTraceProfile& Other) const
	{
		return TracePolicies == Other.TracePolicies;
	}

	bool operator!=(const UTraceProfile& Other) const
	{
		return !(*this == Other);
	}

	bool operator==(const TArray<UTracePolicy*>& OtherPolicies) const
	{
		return TracePolicies == OtherPolicies;
	}

	bool operator!=(const TArray<UTracePolicy*>& OtherPolicies) const
	{
		return !(*this == OtherPolicies);
	}
};