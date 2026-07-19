#include "BaseActors/ModularCharacter.h"
#include "Components/GameFrameworkComponentManager.h"


AModularCharacter::AModularCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AModularCharacter::PreInitializeComponents()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogTemp, Warning, TEXT("AModularCharacter::PreInitializeComponents - GameInstance is not valid."));
		return;
	}

	UGameFrameworkComponentManager* Manager = GameInstance->GetSubsystem<UGameFrameworkComponentManager>();
	if (IsValid(Manager))
	{
		Manager->AddReceiver(this);
	}

	Super::PreInitializeComponents();
}

void AModularCharacter::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
}

void AModularCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (auto* system = GetGameInstance()->GetSubsystem< UGameFrameworkComponentManager >())
	{
		system->RemoveReceiver(this);
	}

	Super::EndPlay(EndPlayReason);
}

void AModularCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AModularCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AModularCharacter::UnPossessed()
{
	Super::UnPossessed();
}

void AModularCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AModularCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();
}

void AModularCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

