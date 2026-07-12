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

void UMessagingController::BroadcastTestMessage(FGameplayTag MessageChannel, FPericulumTestMessage Message)
{
    if (UGameplayMessageSubsystem* MessageSubsystem = GetMessageSubsystem())
    {
        Message.MessageSender = ContextObject;
        Message.WorldTimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0;
        MessageSubsystem->BroadcastMessage(MessageChannel, Message);
	}

}

FGameplayMessageListenerHandle UMessagingController::ListenForTestMessage(FGameplayTag MessageChannel, EGameplayMessageMatch MatchType, const FOnGameplayMessageReceived& Callback)
{
    if (UGameplayMessageSubsystem* MessageSubsystem = GetMessageSubsystem())
    {
        FGameplayMessageListenerHandle Handle = MessageSubsystem->RegisterListener<FPericulumTestMessage>(
            MessageChannel,
            [Callback](FGameplayTag Tag, const FPericulumTestMessage& Message)
            {
                // Execute the dynamic delegate
                if (Callback.IsBound())
                {
                    Callback.Execute(Tag, Message);
                }
            },
            MatchType);
        if (Handle.IsValid())
        {
            RegisteredListeners.Add(Handle);
        }
        return Handle;
    }
	return FGameplayMessageListenerHandle();
    
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