// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ModularAIController.generated.h"

/**
 * 
 */
UCLASS()
class PERICULUM_API AModularAIController : public AAIController
{
	GENERATED_BODY()

public:
	AModularAIController();

	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;
	
};
