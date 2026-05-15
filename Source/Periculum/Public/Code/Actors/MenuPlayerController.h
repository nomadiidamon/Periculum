#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/PericulumPlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PERICULUM_API AMenuPlayerController : public APericulumPlayerController
{
	GENERATED_BODY()
	
public:
	AMenuPlayerController();

	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SetupInputComponent() override;
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;
};
