// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToggleContextProvider.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UToggleContextProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * This interface defines the contract for objects that can provide toggle context information in the Periculum system. Implementing this interface allows an object to participate in toggle state management and provide relevant context for toggles.
 */
class PERICULUM_API IToggleContextProvider
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/// <summary>
	/// Checks if this context provider has a specific toggle tag. This can be used to quickly check for the presence of a relevant toggle without having to retrieve the entire list of tags.
	/// </summary>
	/// <param name="Tag">The name of the toggle tag to check for.</param>
	/// <returns>True if the toggle tag is present, false otherwise.</returns>
	virtual bool HasToggleTag(FName Tag) const = 0;
	
};
