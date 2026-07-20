// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Messages/PericulumMessage.h"
#include "MessagingController.generated.h"


DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGameplayMessageReceived, FGameplayTag, MessageChannel, FPericulumTestMessage, Message);



/**
 * A UObject controller that manages all gameplay message subscriptions and broadcasts for a given context object.
 * Owns all listener handles and cleans them up automatically when StopListeningToAll is called.
 * Intended to be owned by a UMessagingComponent or a UUserWidget - the owner provides world context and GC rooting.
 */

UCLASS(BlueprintType)
class PERICULUM_API UMessagingController : public UObject
{
    GENERATED_BODY()

public:

    /// <summary>
    /// Initializes the messaging controller with the provided outer object and context object.
    /// The context object serves as the reference point for instanced channels and automatic message stamping.
    /// Must be called before any listen or broadcast functions are used.
    /// </summary>
    /// <param name="InOuter">The outer object that owns this controller. Used for GC rooting and world context resolution.</param>
    /// <param name="InContextObject">The UObject this controller speaks for. Stamped as MessageSender on outgoing messages and used to derive instanced channels.</param>
    void Initialize(UObject* InOuter, UObject* InContextObject);

    /// <summary>
    /// Unregisters all active listeners this controller has registered and clears the internal handle list.
    /// Called automatically by the owning component or widget on destruction. Can also be called manually.
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = "Periculum|Messaging")
    void StopListeningToAll();

    /// <summary>
    /// Unregisters a single listener handle and removes it from the internal tracking list.
    /// Use this to stop listening before the controller is destroyed, without unregistering everything.
    /// </summary>
    /// <param name="Handle">The handle returned by a prior ListenForMessage call.</param>
    UFUNCTION(BlueprintCallable, Category = "Periculum|Messaging")
    void StopListening(UPARAM(ref) FGameplayMessageListenerHandle& Handle);

    /// <summary>
    /// Returns the context object this controller was initialized with.
    /// This is the object that serves as the reference for instanced channels and MessageSender stamping.
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = "Periculum|Messaging")
    UObject* GetContextObject() const { return ContextObject.Get(); }

    /// <summary>
    /// Overrides UObject::GetWorld to walk the outer chain for world context.
    /// This allows the controller to resolve a valid world whether it is owned by a component, widget, or other UObject.
    /// </summary>
    virtual UWorld* GetWorld() const override;

    /// <summary>
    /// Derives a deterministic, per-actor instanced gameplay tag from a base tag and a target actor.
    /// The generated tag is registered with the gameplay tag manager at runtime if not already present.
    /// Static so any system can derive the correct channel for a given actor without holding a controller reference.
    /// Format: BaseTag.Instance.ActorName_HexAddress
    /// </summary>
    /// <param name="BaseTag">The base gameplay tag representing the message domain.</param>
    /// <param name="Actor">The actor whose identity is used to generate the instanced channel tag.</param>
    static FGameplayTag GetActorChannel(FGameplayTag BaseTag, const AActor* Actor);

    /// <summary>
    /// Broadcasts a simple test message on the provided channel. This is a Blueprint-friendly wrapper for testing the messaging system.
    /// </summary>
    /// <param name="MessageChannel">The channel to broadcast the message on.</param>
    /// <param name="Message">The message to broadcast.</param>
    UFUNCTION(BlueprintCallable, Category = "Periculum|Messaging")
    void BroadcastTestMessage(FGameplayTag MessageChannel, FPericulumTestMessage Message);

    /// <summary>
    /// Registers a listener for test messages on the provided channel. This is a Blueprint-friendly wrapper for testing the messaging system.
    /// </summary>
    /// <param name="MessageChannel">The channel to listen for messages on.</param>
    /// <param name="MatchType">The matching rules to apply when filtering messages.</param>
    /// <param name="Callback">The function to call when a matching message is received. CANNOT be a Multicast delegate.</param>
    /// <returns>A handle that can be used to unregister the listener.</returns>
    UFUNCTION(BlueprintCallable, Category = "Periculum|Messaging")
    FGameplayMessageListenerHandle ListenForTestMessage(FGameplayTag MessageChannel, EGameplayMessageMatch MatchType, const FOnGameplayMessageReceived& Callback);





    // --- Templated functions below cannot be UFUNCTIONs, but are the primary interface for sending and receiving messages. ---

    /// <summary>
    /// Broadcasts a message on the provided channel.
    /// If the message derives from FPericulumMessage, MessageSender is stamped with the ContextObject
    /// and WorldTimeSeconds is stamped with the current world time if not already set.
    /// </summary>
    /// <param name="MessageChannel">The gameplay tag channel to broadcast on.</param>
    /// <param name="Message">The message struct to broadcast. Passed by value so base fields can be stamped before sending.</param>
    template<typename FMessageType>
    void BroadcastMessage(FGameplayTag MessageChannel, FMessageType Message)
    {
        if constexpr (std::is_base_of_v<FPericulumMessage, FMessageType>)
        {
            if (!Message.MessageSender.IsValid())
            {
                Message.MessageSender = ContextObject;
            }
            Message.WorldTimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0;
        }

        if (UGameplayMessageSubsystem* Subsystem = GetMessageSubsystem())
        {
            Subsystem->BroadcastMessage(MessageChannel, Message);
        }
    }

    /// <summary>
    /// Broadcasts a message on a per-actor instanced channel derived from BaseTag and TargetObject.
    /// Only listeners that registered via ListenForMessageFromContext with the same BaseTag
    /// on a controller whose ContextObject matches TargetObject will receive the message.
    /// If the message derives from FPericulumMessage, MessageReceiver and MessageSender are stamped automatically.
    /// </summary>
    /// <param name="BaseTag">The base gameplay tag used to derive the instanced channel.</param>
    /// <param name="TargetObject">The actor that identifies the instanced channel to broadcast on.</param>
    /// <param name="Message">The message struct to broadcast.</param>
    template<typename FMessageType>
    void BroadcastMessageToObject(FGameplayTag BaseTag, AActor* TargetObject, FMessageType Message)
    {
        if (!TargetObject)
        {
            UE_LOG(LogTemp, Warning,
                TEXT("UMessagingController::BroadcastMessageToObject - TargetObject is null. No message was sent."));
            return;
        }

        const FGameplayTag MessageChannel = GetActorChannel(BaseTag, TargetObject);
        if (!MessageChannel.IsValid()) return;

        if constexpr (std::is_base_of_v<FPericulumMessage, FMessageType>)
        {
            Message.MessageReceiver = TargetObject;
            if (!Message.MessageSender.IsValid()) Message.MessageSender = ContextObject;
            Message.WorldTimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0;
        }

        if (UGameplayMessageSubsystem* Subsystem = GetMessageSubsystem())
        {
            Subsystem->BroadcastMessage(MessageChannel, Message);
        }
    }

    /// <summary>
    /// Registers a listener for messages of the given type on the provided channel.
    /// The listener handle is stored internally and will be unregistered automatically when StopListeningToAll is called.
    /// All other ListenFor variants route through this function.
    /// </summary>
    /// <param name="MessageChannel">The gameplay tag channel to listen on.</param>
    /// <param name="Callback">The function to invoke when a matching message is received.</param>
    template<typename FMessageType>
    FGameplayMessageListenerHandle ListenForMessage(FGameplayTag MessageChannel, TFunction<void(FGameplayTag, const FMessageType&)> Callback)
    {
        UGameplayMessageSubsystem* Subsystem = GetMessageSubsystem();
        if (!Subsystem)
        {
            UE_LOG(LogTemp, Warning,
                TEXT("UMessagingController::ListenForMessage - subsystem unavailable. No listener was registered."));
            return FGameplayMessageListenerHandle();
        }

        FGameplayMessageListenerHandle Handle =
            Subsystem->RegisterListener<FMessageType>(MessageChannel, Callback);
        RegisteredListeners.Add(Handle);
        return Handle;
    }

    /// <summary>
    /// Registers a listener on the instanced channel derived from this controller's ContextObject.
    /// Only receives messages broadcast via BroadcastMessageToObject targeting the same object.
    /// Requires the ContextObject to be an AActor, as instanced channels are derived from actor identity.
    /// </summary>
    /// <param name="BaseTag">The base gameplay tag used to derive the instanced channel.</param>
    /// <param name="Callback">The function to invoke when a matching message is received.</param>
    template<typename FMessageType>
    FGameplayMessageListenerHandle ListenForMessageFromContext(FGameplayTag BaseTag, TFunction<void(FGameplayTag, const FMessageType&)> Callback)
    {
        AActor* ContextActor = Cast<AActor>(ContextObject.Get());
        if (!ContextActor)
        {
            UE_LOG(LogTemp, Warning,
                TEXT("UMessagingController::ListenForMessageFromContext - ContextObject is null or not an AActor. "
                    "Instanced channels require an AActor as the ContextObject. No listener was registered."));
            return FGameplayMessageListenerHandle();
        }

        const FGameplayTag MessageChannel = GetActorChannel(BaseTag, ContextActor);
        if (!MessageChannel.IsValid()) return FGameplayMessageListenerHandle();

        return ListenForMessage<FMessageType>(MessageChannel, Callback);
    }

    /// <summary>
    /// Registers a listener on a channel that filters incoming messages to only those
    /// where MessageReceiver matches the provided object.
    /// All messages on the channel are still delivered by the subsystem. Filtering occurs in the callback.
    /// Requires FMessageType to derive from FPericulumMessage.
    /// </summary>
    /// <param name="MessageChannel">The gameplay tag channel to listen on.</param>
    /// <param name="ReceiverFilter">The UObject that MessageReceiver must match for the callback to fire.</param>
    /// <param name="Callback">The function to invoke when a matching message is received.</param>
    template<typename FMessageType>
    FGameplayMessageListenerHandle ListenForMessageTargetingObject(FGameplayTag MessageChannel, UObject* ReceiverFilter, TFunction<void(FGameplayTag, const FMessageType&)> Callback)
    {
        TWeakObjectPtr<UObject> WeakFilter = ReceiverFilter;
        return ListenForMessage<FMessageType>(MessageChannel,
            [WeakFilter, Callback](FGameplayTag Tag, const FMessageType& Message)
            {
                if constexpr (std::is_base_of_v<FPericulumMessage, FMessageType>)
                {
                    if (Message.MessageReceiver.Get() != WeakFilter.Get()) return;
                }
                Callback(Tag, Message);
            });
    }

    /// <summary>
    /// Registers a listener on a channel that filters incoming messages to only those
    /// where MessageSender matches the provided object.
    /// All messages on the channel are still delivered by the subsystem - filtering occurs in the callback.
    /// Requires FMessageType to derive from FPericulumMessage.
    /// </summary>
    /// <param name="MessageChannel">The gameplay tag channel to listen on.</param>
    /// <param name="SenderFilter">The UObject that MessageSender must match for the callback to fire.</param>
    /// <param name="Callback">The function to invoke when a matching message is received.</param>
    template<typename FMessageType>
    FGameplayMessageListenerHandle ListenForMessageFromObject(FGameplayTag MessageChannel, UObject* SenderFilter, TFunction<void(FGameplayTag, const FMessageType&)> Callback)
    {
        TWeakObjectPtr<UObject> WeakFilter = SenderFilter;
        return ListenForMessage<FMessageType>(MessageChannel,
            [WeakFilter, Callback](FGameplayTag Tag, const FMessageType& Message)
            {
                if constexpr (std::is_base_of_v<FPericulumMessage, FMessageType>)
                {
                    if (Message.MessageSender.Get() != WeakFilter.Get()) return;
                }
                Callback(Tag, Message);
            });
    }

private:

    UGameplayMessageSubsystem* GetMessageSubsystem() const;

    /// <summary>
    /// The UObject this controller speaks for. Used to stamp MessageSender on outgoing messages
    /// and to derive instanced channels via GetActorChannel.
    /// </summary>
    TWeakObjectPtr<UObject> ContextObject;

    /// <summary>
    /// All listener handles registered through this controller.
    /// Stored here so they can be unregistered in bulk on destruction or on demand.
    /// </summary>
    TArray<FGameplayMessageListenerHandle> RegisteredListeners;
};
