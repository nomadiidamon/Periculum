#pragma once

#include "CoreMinimal.h"
#include "BaseActors/PericulumPlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * MenuPlayerController is the player controller class for the menu system.
 */
UCLASS()
class PERICULUM_API AMenuPlayerController : public APericulumPlayerController
{
	GENERATED_BODY()
	
public:
	AMenuPlayerController();

	/// <summary>
	/// Initializes the player controller before components are initialized. This is where you can set up any necessary variables or state before the game begins.
	/// </summary>
	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

protected:
	/// <summary>
	/// Overrides the base implementation to initialize and bind input handlers on the object's input component. Use this to register input actions and axis mappings.Sets up the input component for the player controller. This is where you can bind input actions and axes to functions that will handle them.
	/// </summary>
	virtual void SetupInputComponent() override;
	
	/// <summary>
	/// Behavior when the player controller possesses a pawn. This virtual method is called when the controller takes control of a pawn, allowing for custom logic to be executed upon possession. Override this method to implement specific behavior when possessing a pawn.
	/// </summary>
	/// <param name="InPawn">The pawn being possessed.</param>
	virtual void OnPossess(APawn* InPawn) override;

	/// <summary>
	/// Behavior when the player controller unpossesses a pawn. This virtual method is called when the controller releases control of a pawn, allowing for custom logic to be executed upon unpossession. Override this method to implement specific behavior when unpossessing a pawn.
	/// </summary>
	virtual void OnUnPossess() override;
};
