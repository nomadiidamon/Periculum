// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActors/ModularCharacter.h"
#include "BasePericulumCharacter.generated.h"

class UMessagingComponent;
class UTraceComponent;
class UToggleComponent;
class UTagContainerComponent;

/**
 * 
 */
UCLASS()
class PERICULUM_API ABasePericulumCharacter : public AModularCharacter
{
	GENERATED_BODY()
	
public:
	ABasePericulumCharacter();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void UnPossessed() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;
	virtual void OnRep_PlayerState() override;

public:
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UMessagingComponent> MessagingComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UTraceComponent> TraceComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UToggleComponent> ToggleComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UTagContainerComponent> TagContainer;

public:
	UFUNCTION(BlueprintCallable, Category = "Components")
	UTagContainerComponent* GetTagContainer() const { return TagContainer; }

	UFUNCTION(BlueprintCallable, Category = "Components")
	UMessagingComponent* GetMessagingComponent() const { return MessagingComponent; }

	UFUNCTION(BlueprintCallable, Category = "Components")
	UTraceComponent* GetTraceComponent() const { return TraceComponent; }

	UFUNCTION(BlueprintCallable, Category = "Components")
	UToggleComponent* GetToggleComponent() const { return ToggleComponent; }
};
