#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ModularPawn.generated.h"

UCLASS()
class PERICULUM_API AModularPawn : public APawn
{
	GENERATED_BODY()

public:
	AModularPawn();

	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void UnPossessed() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
