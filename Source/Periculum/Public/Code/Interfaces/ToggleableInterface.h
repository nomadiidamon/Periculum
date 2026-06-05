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
 * 
 */
class PERICULUM_API IToggleableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Toggle the state of the object. If bEnabled is true, enable the object; if false, disable it.
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void Enable();

	// Toggle the state of the object. If bEnabled is true, enable the object; if false, disable it.
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void Disable();

	// Set the enabled state of the object. If bEnabled is true, enable the object; if false, disable it.
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void SetEnabled(bool bEnabled);

	// Get the enabled state of the object. Returns true if the object is enabled, false otherwise.
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    bool IsEnabled() const;

};
