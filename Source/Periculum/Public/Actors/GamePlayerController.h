#pragma once

#include "CoreMinimal.h"
#include "BaseActors/PericulumPlayerController.h"
#include "GamePlayerController.generated.h"

/**
 * GamePlayerController is the player controller class for the standard game mode.
 */

UCLASS()
class PERICULUM_API AGamePlayerController : public APericulumPlayerController
{
	GENERATED_BODY()
	
public:
	AGamePlayerController();

	/// <summary>
	/// Performs pre-initialization of the object's components. This virtual method is called during the setup phase and can be overridden to configure or prepare components before the main initialization.
	/// </summary>
	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

protected:
	/// <summary>
	/// Sets up the input component for the player controller. This virtual method is called to bind input actions and axes to functions, allowing the player to interact with the game. Override this method to customize input handling.
	/// </summary>
	virtual void SetupInputComponent() override;

	/// <summary>
	/// Behavior when the player controller possesses a pawn. This virtual method is called when the controller takes control of a pawn, allowing for custom logic to be executed upon possession. Override this method to implement specific behavior when possessing a pawn.
	/// </summary>
	/// <param name="InPawn"></param>
	virtual void OnPossess(APawn* InPawn) override;

	/// <summary>
	/// Behavior when the player controller unpossesses a pawn. This virtual method is called when the controller relinquishes control of a pawn, allowing for custom logic to be executed upon unpossession. Override this method to implement specific behavior when unpossessing a pawn.
	/// </summary>
	virtual void OnUnPossess() override;

};