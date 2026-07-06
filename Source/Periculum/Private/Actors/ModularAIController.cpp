#include "Actors/ModularAIController.h"
#include "Components/GameFrameworkComponentManager.h"

AModularAIController::AModularAIController()
{
}

void AModularAIController::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (auto* gi = GetGameInstance())
	{
		if (auto* system = gi->GetSubsystem< UGameFrameworkComponentManager >())
		{
			system->AddReceiver(this);
		}
	}
}

void AModularAIController::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();	
}

void AModularAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (auto* system = GetGameInstance()->GetSubsystem< UGameFrameworkComponentManager >())
	{
		system->RemoveReceiver(this);
	}

	Super::EndPlay(EndPlayReason);
}

void AModularAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AModularAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
