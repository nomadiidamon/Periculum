// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MenuPlayerController.h"

AMenuPlayerController::AMenuPlayerController()
{
}

void AMenuPlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMenuPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMenuPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AMenuPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AMenuPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}
