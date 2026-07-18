// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataAssets/TraceProfile.h"
#include "../TracePolicies/CameraTracePolicy.h"
#include "TraceStatics.generated.h"

class UTracePolicy;
class USphereTracePolicy;
class UCameraComponent;

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

	UFUNCTION(BlueprintCallable, Category = "Trace")
	static USphereTracePolicy* MakeSphereTracePolicy(FVector StartOffset, FVector EndOffset, float Radius, ECollisionChannel TraceChannel, bool bMultiTrace, bool bDrawDebug, FName PolicyName, EPolicyStackPriority StackPriority, int32 PriorityScalar);

	UFUNCTION(BlueprintCallable, Category = "Trace")
	static UCameraTracePolicy* MakeCameraTracePolicy(ECameraTraceType TraceType, UCameraComponent* CameraComponent, FVector StartOffset, FVector EndOffset, float SphereRadius, float CapsuleRadius, float CapsuleHalfHeight, FVector BoxHalfSize, ECollisionChannel TraceChannel, bool bMultiTrace, bool bDrawDebug, FName PolicyName, EPolicyStackPriority StackPriority, int32 PriorityScalar);
};
