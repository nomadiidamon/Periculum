// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MessagingComponent.h"
#include "Controllers/MessagingController.h"

UMessagingComponent::UMessagingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMessagingComponent::BeginPlay()
{
	Super::BeginPlay();

	Controller = NewObject<UMessagingController>(this);
	Controller->Initialize(this, GetOwner());
}

void UMessagingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Controller)
	{
		Controller->StopListeningToAll();
		Controller = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

FGameplayTag UMessagingComponent::GetActorChannel(FGameplayTag BaseTag, const AActor* Actor)
{
	return UMessagingController::GetActorChannel(BaseTag, Actor);
}

void UMessagingComponent::StopListening(UPARAM(ref)FGameplayMessageListenerHandle& ListenerHandle)
{
	if (Controller) 
	{
		Controller->StopListening(ListenerHandle);
	}
}

void UMessagingComponent::StopListeningToAll()
{
	if (Controller) 
	{
		Controller->StopListeningToAll();
	}
}

