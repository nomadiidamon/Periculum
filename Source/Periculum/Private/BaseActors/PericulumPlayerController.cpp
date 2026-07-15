// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActors/PericulumPlayerController.h"
#include "Components/GameFrameworkComponentManager.h"


APericulumPlayerController::APericulumPlayerController()
{
}

void APericulumPlayerController::PreInitializeComponents()
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

void APericulumPlayerController::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);

	Super::BeginPlay();
}

void APericulumPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (auto* system = GetGameInstance()->GetSubsystem< UGameFrameworkComponentManager >())
	{
		system->RemoveReceiver(this);
	}

	Super::EndPlay(EndPlayReason);
}

void APericulumPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APericulumPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void APericulumPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void APericulumPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}
