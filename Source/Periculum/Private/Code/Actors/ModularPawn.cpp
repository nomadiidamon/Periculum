#include "Code/Actors/ModularPawn.h"
#include "Components/GameFrameworkComponentManager.h"

AModularPawn::AModularPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AModularPawn::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (UGameFrameworkComponentManager* Manager =
		GetGameInstance()->GetSubsystem<UGameFrameworkComponentManager>())
	{
		Manager->AddReceiver(this);
	}
}

void AModularPawn::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
}

void AModularPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (auto* system = GetGameInstance()->GetSubsystem< UGameFrameworkComponentManager >())
	{
		system->RemoveReceiver(this);
	}

	Super::EndPlay(EndPlayReason);
}

void AModularPawn::UnPossessed()
{
	Super::UnPossessed();
}

void AModularPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AModularPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AModularPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

