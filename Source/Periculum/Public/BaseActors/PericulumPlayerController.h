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

	/// <summary>
	/// Lifecycle hook invoked before component initialization. Overrides the base-class implementation to perform any necessary pre-initialization tasks.
	/// Used to register this PlayerController with the UGameFrameworkComponentManager to receive modular components and functionality before it fully initializes.
	/// </summary>
	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

};
