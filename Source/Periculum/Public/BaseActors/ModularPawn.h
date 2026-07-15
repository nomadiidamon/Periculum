#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ModularPawn.generated.h"

/**
 * A modular pawn that can be extended with components and functionality.
*/

UCLASS()
class PERICULUM_API AModularPawn : public APawn
{
	GENERATED_BODY()

public:
	AModularPawn();

	/// <summary>
	/// Lifecycle hook invoked before component initialization. Overrides the base-class implementation to perform any necessary pre-initialization tasks.
	/// Used to register this Pawn with the UGameFrameworkComponentManager to receive modular components and functionality before it fully initializes.
	/// </summary>
	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void UnPossessed() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
