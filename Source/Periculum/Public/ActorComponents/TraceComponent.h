// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/TraceableInterface.h"
#include "Defines/TraceTypes.h"
#include "TraceComponent.generated.h"


class UTraceProfile;
class UTracePolicy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTraceCompleted, const FTraceResult&, Result);

/**
 * UTraceComponent is responsible for performing traces based on a specified trace profile and its associated policies.
 * It can be configured to automatically perform traces at regular intervals or manually triggered.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PERICULUM_API UTraceComponent : public UActorComponent, public ITraceableInterface
{
	GENERATED_BODY()

public:
	UTraceComponent();

	virtual FTraceResult PerformTrace_Implementation() override;
	virtual FTraceResult GetLastTraceResult_Implementation() const override;

	/// <summary>
	/// Returns the currently active trace profile. This function is exposed to Blueprints and does not modify the object state.
	/// </summary>
	/// <returns>Pointer to the active UTraceProfile. May be nullptr if no profile is active.</returns>
	UFUNCTION(BlueprintCallable)
	UTraceProfile* GetActiveProfile() const { return Profile; }

	/// <summary>
	/// Returns the currently active trace policies. This function is exposed to Blueprints and does not modify the object state.
	/// </summary>
	/// <returns>A TArray<UTracePolicy*> that contains the active trace policies.</returns>
	UFUNCTION(BlueprintCallable)
	TArray<UTracePolicy*> GetActivePolicies() const { return BuildPolicyStack(); }

	/// <summary>
	/// Performs a trace using the first policy that matches the specified tag. This function is exposed to Blueprints and allows for targeted tracing based on policy tags.
	/// </summary>
	/// <param name="Tag">The tag of the policy to use for tracing.</param>
	/// <returns>The result of the trace performed by the matching policy. Will be empty if no matching policy is found.</returns>
	UFUNCTION(BlueprintCallable)
	FTracePolicyResult PerformTraceByTag(FName Tag);

public:
	/// <summary>
	/// A dynamic multicast delegate that is broadcast when a trace is completed. This allows other components or Blueprints to respond to trace results.
	/// </summary>
	UPROPERTY(BlueprintAssignable)
	FTraceCompleted OnTraceCompleted;

	/// <summary>
	/// Whether the trace component should automatically perform traces at regular intervals. If true, traces will be performed every TraceInterval seconds.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TraceComponent")
	bool bAutoTrace = false;

	/// <summary>
	/// The interval, in seconds, at which automatic traces are performed when bAutoTrace is true. This value is clamped to a minimum of 0.0 seconds.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TraceComponent", meta = (EditCondition = "bAutoTrace", ClampMin = "0.0"))
	float TraceInterval = 0.1f;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// Returns a combined stack of trace policies from the active profile and any runtime policies. This function is used internally to determine which policies to apply during a trace.
	/// </summary>
	/// <returns>A TArray<UTracePolicy*> containing the combined stack of trace policies.</returns>
	TArray<UTracePolicy*> BuildPolicyStack() const;

protected:
	/// <summary>
	/// The trace profile that defines the set of policies to be applied during tracing. This property is editable in the editor and read-only in Blueprints.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TraceComponent")
	TObjectPtr<UTraceProfile> Profile;

	/// <summary>
	/// The array of runtime policies that can be added or modified at runtime. These policies are instanced and editable in the editor, allowing for dynamic behavior during gameplay.
	/// </summary>
	UPROPERTY(EditAnywhere, Instanced, Category = "TraceComponent")
	TArray<UTracePolicy*> RuntimePolicies;

	/// <summary>
	/// The result of the most recent trace performed by this component. This property is read-only in Blueprints and provides access to the last trace result for further processing or decision-making.
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "TraceComponent")
	FTraceResult LastTraceResult;

private:
	/// <summary>
	/// Used internally to track the time elapsed since the last trace was performed. This is used in conjunction with TraceInterval to determine when the next automatic trace should occur.
	/// </summary>
	float TimeSinceLastTrace = 0.0f;
};