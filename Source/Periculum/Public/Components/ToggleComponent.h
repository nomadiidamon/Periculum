// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/ToggleableInterface.h"
#include "ToggleComponent.generated.h"


class UToggleProfile;
class UTogglePolicy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToggleStateChanged, bool, bEnabled);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERICULUM_API UToggleComponent : public UActorComponent, public IToggleableInterface
{
	GENERATED_BODY()

public:	
	UToggleComponent();

    virtual void Enable_Implementation() override;
    virtual void Disable_Implementation() override;
    virtual void SetEnabled_Implementation(bool bNewState) override;
    virtual bool IsEnabled_Implementation() const override;

    UFUNCTION(BlueprintCallable)
    void DisableBySource(FName Source);

    UFUNCTION(BlueprintCallable)
    void EnableBySource(FName Source);

    UFUNCTION(BlueprintCallable)
	UToggleProfile* GetActiveProfile() const { return Profile; }

	UFUNCTION(BlueprintCallable)
	TArray<UTogglePolicy*> GetActivePolicies() const { return BuildPolicyStack(); }

public:
    UPROPERTY(BlueprintAssignable)
    FToggleStateChanged OnToggleChanged;

protected:
	virtual void BeginPlay() override;

    void ExecutePolicies(bool bNewState);

    TArray<UTogglePolicy*> BuildPolicyStack() const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bEnabled = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UToggleProfile> Profile;

    UPROPERTY(EditAnywhere, Instanced)
    TArray<UTogglePolicy*> RuntimePolicies;

    UPROPERTY()
    TSet<FName> DisableSources;


private:
    UFUNCTION()
	void HandleToggleChange(bool bNewState);

		
};
