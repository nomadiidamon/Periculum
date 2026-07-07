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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PERICULUM_API UTraceComponent : public UActorComponent, public ITraceableInterface
{
	GENERATED_BODY()

public:
	UTraceComponent();

	virtual FTraceResult PerformTrace_Implementation() override;
	virtual FTraceResult GetLastTraceResult_Implementation() const override;

	UFUNCTION(BlueprintCallable)
	UTraceProfile* GetActiveProfile() const { return Profile; }

	UFUNCTION(BlueprintCallable)
	TArray<UTracePolicy*> GetActivePolicies() const { return BuildPolicyStack(); }

	// Executes only the policy whose PolicyTag matches the given tag.
	UFUNCTION(BlueprintCallable)
	FTracePolicyResult PerformTraceByTag(FName Tag);

public:
	UPROPERTY(BlueprintAssignable)
	FTraceCompleted OnTraceCompleted;

	// When true, PerformTrace runs automatically every TraceInterval seconds.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TraceComponent")
	bool bAutoTrace = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TraceComponent", meta = (EditCondition = "bAutoTrace", ClampMin = "0.0"))
	float TraceInterval = 0.1f;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<UTracePolicy*> BuildPolicyStack() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TraceComponent")
	TObjectPtr<UTraceProfile> Profile;

	UPROPERTY(EditAnywhere, Instanced, Category = "TraceComponent")
	TArray<UTracePolicy*> RuntimePolicies;

	UPROPERTY(BlueprintReadOnly, Category = "TraceComponent")
	FTraceResult LastTraceResult;

private:
	float TimeSinceLastTrace = 0.0f;
};