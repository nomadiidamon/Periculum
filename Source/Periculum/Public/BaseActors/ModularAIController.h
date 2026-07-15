// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ModularAIController.generated.h"

/**
 * A modular AI controller that can be extended with components and functionality.
 */

UCLASS()
class PERICULUM_API AModularAIController : public AAIController
{
	GENERATED_BODY()

public:
	AModularAIController();

	/// <summary>
	/// Lifecycle hook invoked before component initialization. Overrides the base-class implementation to perform any necessary pre-initialization tasks.
	/// Used to register this AIController with the UGameFrameworkComponentManager to receive modular components and functionality before it fully initializes.
	/// </summary>
	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;
	
};
