// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Objects/TracePolicies/TracePolicy.h"
#include "TraceProfile.generated.h"

/**
 * 
 */
class UTracePolicy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTraceProfileChanged, UTraceProfile*, NewProfile);

UCLASS(BlueprintType)
class PERICULUM_API UTraceProfile : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "TraceProfile")
	TArray<UTracePolicy*> TracePolicies;

public:
	FOnTraceProfileChanged OnProfileChanged;

private:
	friend class UTraceStatics;

private:
	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void AddPolicy(UTracePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void AddPolicies(const TArray<UTracePolicy*>& Policies);

	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void AddUniquePolicy(UTracePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void AddUniquePolicies(const TArray<UTracePolicy*>& Policies);

	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void RemovePolicy(UTracePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void RemovePolicies(const TArray<UTracePolicy*>& Policies);

	UFUNCTION(BlueprintCallable, Category = "TraceProfile")
	void ClearPolicies();

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