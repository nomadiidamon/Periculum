#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PericulumPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PERICULUM_API APericulumPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APericulumPlayerController();

	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

};
