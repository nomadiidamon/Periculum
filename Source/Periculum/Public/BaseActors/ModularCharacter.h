#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ModularCharacter.generated.h"

/**
 * A modular character that can be extended with components and functionality.
 */

UCLASS()
class PERICULUM_API AModularCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AModularCharacter();

	/// <summary>
	/// Lifecycle hook invoked before component initialization. Overrides the base-class implementation to perform any necessary pre-initialization tasks.
	/// Used to register this Character with the UGameFrameworkComponentManager to receive modular components and functionality before it fully initializes.
	/// </summary>
	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void UnPossessed() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_Controller() override;

	virtual void OnRep_PlayerState() override;

};
