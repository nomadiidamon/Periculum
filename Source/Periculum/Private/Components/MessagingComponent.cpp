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

FGameplayTag UMessagingComponent::GetActorChannel(FGameplayTag BaseTag, const AActor* Actor)
{
	return UMessagingController::GetActorChannel(BaseTag, Actor);
}


void UMessagingComponent::BroadcastTestMessage(FGameplayTag MessageChannel, FPericulumTestMessage Message)
{
	if (Controller)
	{
		Controller->BroadcastTestMessage(MessageChannel, Message);
	}
}

FGameplayMessageListenerHandle UMessagingComponent::ListenForTestMessage(FGameplayTag MessageChannel, EGameplayMessageMatch MatchType, const FOnGameplayMessageReceived& Callback)
{
	if (Controller)
	{
		return Controller->ListenForTestMessage(MessageChannel, MatchType, Callback);
	}
	return FGameplayMessageListenerHandle();

}
