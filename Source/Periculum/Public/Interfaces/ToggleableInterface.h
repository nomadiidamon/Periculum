// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToggleableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UToggleableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * This interface defines the contract for objects that can be toggled on or off in the Periculum system. Implementing this interface allows an object to participate in toggle state management, enabling or disabling its functionality as needed.
 */
class PERICULUM_API IToggleableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    /// <summary>
	/// Toggles the state of the object. If bEnabled is true, enable the object; if false, disable it.
    /// </summary>
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void Enable();

    /// <summary>
	/// Toggles the state of the object. If bEnabled is true, enable the object; if false, disable it.
    /// </summary>
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void Disable();

    /// <summary>
	/// Sets the enabled state of the object. If bEnabled is true, enable the object; if false, disable it.
    /// </summary>
    /// <param name="bEnabled">The new enabled state of the object.</param>
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void SetEnabled(bool bEnabled);

    /// <summary>
	/// Gets the enabled state of the object. Returns true if the object is enabled, false otherwise.
    /// </summary>
    /// <returns>True if the object is enabled, false otherwise.</returns>
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    bool IsEnabled() const;

};
