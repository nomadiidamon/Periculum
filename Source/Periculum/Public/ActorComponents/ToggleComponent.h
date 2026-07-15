// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/ToggleableInterface.h"
#include "ToggleComponent.generated.h"


class UToggleProfile;
class UTogglePolicy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToggleStateChanged, bool, bEnabled);

/**
 * UToggleComponent is a component that can be attached to an actor to provide toggle functionality.
 * It allows enabling and disabling the component, and it can execute policies based on the toggle state.
 */


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

    /// <summary>
	/// Disables the toggle component based on a specific source. The component will remain disabled until all sources that have disabled it are removed.
    /// </summary>
    /// <param name="Source">The name of the source that is disabling the component.</param>
    UFUNCTION(BlueprintCallable)
    void DisableBySource(FName Source);

    /// <summary>
	/// Enables the toggle component based on a specific source. The component will only be enabled if all sources that have disabled it are removed.
    /// </summary>
    /// <param name="Source">The name of the source that is enabling the component.</param>
    UFUNCTION(BlueprintCallable)
    void EnableBySource(FName Source);

    /// <summary>
	/// Gets the active toggle profile associated with this component. The profile contains the policies that determine how the toggle behaves.
    /// </summary>
    /// <returns>The active toggle profile.</returns>
    UFUNCTION(BlueprintCallable)
	UToggleProfile* GetActiveProfile() const { return Profile; }

	/// <summary>
	/// Retrieves the currently active toggle policies as an array.
	/// </summary>
	/// <returns>A TArray<UTogglePolicy*> containing pointers to the active policies. The array is returned by value.</returns>
	UFUNCTION(BlueprintCallable)
	TArray<UTogglePolicy*> GetActivePolicies() const { return BuildPolicyStack(); }

public:
    /// <summary>
	/// Dynamic multicast delegate that is triggered when the toggle state changes. It passes a boolean parameter indicating the new state (enabled or disabled).
    /// </summary>
    UPROPERTY(BlueprintAssignable)
    FToggleStateChanged OnToggleChanged;

protected:
	virtual void BeginPlay() override;

    /// <summary>
    /// Enables or disables policy execution based on the specified state.
    /// </summary>
    /// <param name="bNewState">If true, enable or apply the new policies; if false, disable or revert the policies.</param>
    void ExecutePolicies(bool bNewState);

    /// <summary>
	/// Combines the policies from the active profile and runtime policies into a single stack, sorted by priority. This stack is used to determine the effective behavior of the toggle component.
    /// </summary>
    /// <returns></returns>
    TArray<UTogglePolicy*> BuildPolicyStack() const;

protected:
    /// <summary>
	/// The enabled state of the toggle component. If true, the component is enabled; if false, it is disabled.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bEnabled = true;

    /// <summary>
	/// The toggle profile associated with this component. The profile contains the policies that determine how the toggle behaves.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UToggleProfile> Profile;

    /// <summary>
	/// The array of runtime policies that can be added or modified at runtime. These policies are combined with the profile's policies to determine the effective behavior of the toggle component.
    /// </summary>
    UPROPERTY(EditAnywhere, Instanced)
    TArray<UTogglePolicy*> RuntimePolicies;

    /// <summary>
	/// The set of sources that have disabled the toggle component. The component will remain disabled until all sources that have disabled it are removed.
    /// </summary>
    UPROPERTY()
    TSet<FName> DisableSources;

private:
    /// <summary>
	/// Handles a change in a toggle's state. Broadcasts the OnToggleChanged delegate and executes the appropriate policies based on the new state.
    /// </summary>
    /// <param name="bNewState">The new state of the toggle: true if enabled/on, false if disabled/off.</param>
    UFUNCTION()
	void HandleToggleChange(bool bNewState);

		
};
