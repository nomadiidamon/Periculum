// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/MessagingController.h"
#include "GameplayTagsManager.h"


void UMessagingController::Initialize(UObject* InOuter, UObject* InContextObject)
{
	Rename(nullptr, InOuter);
	ContextObject = InContextObject;
}

void UMessagingController::StopListeningToAll()
{
    for (FGameplayMessageListenerHandle& Handle : RegisteredListeners)
    {
        Handle.Unregister();
    }
    RegisteredListeners.Reset();
}

void UMessagingController::StopListening(UPARAM(ref) FGameplayMessageListenerHandle& Handle)
{
    Handle.Unregister();

    // FGameplayMessageListenerHandle has no operator==, so we need to use a lambda to remove the handle from the array
    RegisteredListeners.RemoveAll([](const FGameplayMessageListenerHandle& Handle)
        {
            return !Handle.IsValid();
        });
}

UWorld* UMessagingController::GetWorld() const
{
    if (UObject* Outer = GetOuter())
    {
        return Outer->GetWorld();
    }
    return nullptr;
}

FGameplayTag UMessagingController::GetActorChannel(FGameplayTag BaseTag, const AActor* Actor)
{
    if (!Actor || !BaseTag.IsValid()) return FGameplayTag();

    const FName ChannelName = FName(*FString::Printf(
        TEXT("%s.Instance.%s_%p"),
        *BaseTag.ToString(),
        *Actor->GetName(),
        Actor));

    return UGameplayTagsManager::Get().AddNativeGameplayTag(
        ChannelName,
        TEXT("Auto-generated per-actor instance channel"));
}

UGameplayMessageSubsystem* UMessagingController::GetMessageSubsystem() const
{
    if (UWorld* World = GetWorld())
    {
        return UGameInstance::GetSubsystem<UGameplayMessageSubsystem>(
            World->GetGameInstance());
    }
    return nullptr;
}