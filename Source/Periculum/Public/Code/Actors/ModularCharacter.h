#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ModularCharacter.generated.h"

UCLASS()
class PERICULUM_API AModularCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AModularCharacter();

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
