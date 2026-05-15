#include "Code/Actors/GamePlayerController.h"

AGamePlayerController::AGamePlayerController()
{

}

void AGamePlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AGamePlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AGamePlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}
