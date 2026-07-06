#pragma once

#include "CoreMinimal.h"
#include "Actors/PericulumPlayerController.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PERICULUM_API AGamePlayerController : public APericulumPlayerController
{
	GENERATED_BODY()
	
public:
	AGamePlayerController();

	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

};