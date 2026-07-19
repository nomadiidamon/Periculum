// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActors/BasePericulumCharacter.h"

#include "ActorComponents/MessagingComponent.h"
#include "ActorComponents/TraceComponent.h"
#include "ActorComponents/ToggleComponent.h"
#include "ActorComponents/TagContainerComponent.h"

#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"


ABasePericulumCharacter::ABasePericulumCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;


	MessagingComponent = CreateDefaultSubobject<UMessagingComponent>(TEXT("MessagingComponent"));

	TraceComponent = CreateDefaultSubobject<UTraceComponent>(TEXT("TraceComponent"));

	ToggleComponent = CreateDefaultSubobject<UToggleComponent>(TEXT("ToggleComponent"));

	TagContainer = CreateDefaultSubobject<UTagContainerComponent>(TEXT("TagContainer"));
}

void ABasePericulumCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePericulumCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABasePericulumCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePericulumCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasePericulumCharacter::UnPossessed()
{
	Super::UnPossessed();
}

void ABasePericulumCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ABasePericulumCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();
}

void ABasePericulumCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}
