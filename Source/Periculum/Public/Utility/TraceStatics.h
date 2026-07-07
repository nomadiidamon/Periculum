// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Objects/DataAssets/TraceProfile.h"
#include "TraceStatics.generated.h"

/**
 * 
 */
UCLASS()
class PERICULUM_API UTraceStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Trace")
	static FTraceResult PerformTrace(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Trace")
	static FTracePolicyResult PerformTraceByTag(AActor* Target, FName Tag);

	UFUNCTION(BlueprintCallable, Category = "Trace")
	static UTraceProfile* GetTraceProfile(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Trace")
	static void AddPolicy(AActor* Target, UTracePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "Trace")
	static void AddUniquePolicy(AActor* Target, UTracePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "Trace")
	static void AddPolicies(AActor* Target, const TArray<UTracePolicy*>& Policies);

	UFUNCTION(BlueprintCallable, Category = "Trace")
	static void RemovePolicy(AActor* Target, UTracePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "Trace")
	static void RemovePolicies(AActor* Target, const TArray<UTracePolicy*>& Policies);

	UFUNCTION(BlueprintCallable, Category = "Trace")
	static void ClearPolicies(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Trace")
	static bool ActorIsTraceable(AActor* Target);
};
