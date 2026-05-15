// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/PericulumPlayerController.h"

APericulumPlayerController::APericulumPlayerController()
{
}

void APericulumPlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void APericulumPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void APericulumPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
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
