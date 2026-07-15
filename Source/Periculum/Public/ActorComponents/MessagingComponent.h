// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Messages/PericulumMessage.h"
#include "../Defines/PericulumLog.h"
#include "../Controllers/MessagingController.h"
#include "MessagingComponent.generated.h"

/**
* An actor component that provides gameplay message broadcasting and listening to its owning actor. Owns a UMessagingController which manages all handle lifetimes.
* It allows for decoupled communication between different parts of the game, enabling components to send and receive messages without needing direct references to each other.
* All listener handles are automatically unregistered when the component's owner is destroyed via EndPlay. Add this component to any actor that needs to participate in the Periculum messaging system.
* A basic message struct, FPericulumMessage, is provided as a parent struct to define custom messages in the Periculum messaging system. This struct includes information about the sender, the time the message was sent, and optional context tags.
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PERICULUM_API UMessagingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMessagingComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	/// <summary>
	/// Returns the underlying messaging controller owned by this component.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Periculum|Messaging")
	UMessagingController* GetMessagingController() const { return Controller; }

	/// <summary>
	/// Unregisters all active listeners registered through this component and clears the internal handle list.
	/// Called automatically on EndPlay. Can also be called manually to reset all subscriptions at runtime.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Periculum|Messaging")
	void StopListeningToAll();

	/// <summary>
	/// Unregisters a single listener handle and removes it from the internal tracking list.
	/// </summary>
	/// <param name="Handle">The handle returned by a prior ListenForMessage call.</param>
	UFUNCTION(BlueprintCallable, Category = "Periculum|Messaging")
	void StopListening(UPARAM(ref) FGameplayMessageListenerHandle& Handle);

	/// <summary>
	/// Derives a deterministic, per-actor instanced gameplay tag from a base tag and a target actor.
	/// The generated tag is registered with the gameplay tag manager at runtime if not already present.
	/// Static so any system can derive the correct channel for a given actor without holding a controller reference.
	/// Format: BaseTag.Instance.ActorName_HexAddress
	/// </summary>
	/// <param name="BaseTag">The base gameplay tag representing the message domain.</param>
	/// <param name="Actor">The actor whose identity is used to generate the instanced channel tag.</param>
	static FGameplayTag GetActorChannel(FGameplayTag BaseTag, const AActor* Actor);


	UFUNCTION(BlueprintCallable, Category = "Periculum|Messaging")
	void BroadcastTestMessage(FGameplayTag MessageChannel, FPericulumTestMessage Message);


	UFUNCTION(BlueprintCallable, Category = "Periculum|Messaging")
	FGameplayMessageListenerHandle ListenForTestMessage(FGameplayTag MessageChannel, EGameplayMessageMatch MatchType, const FOnGameplayMessageReceived& Callback);

	// --- Templated methods below are not exposed to Blueprints, but can be used in C++ code.

	/// <summary>
    /// Broadcasts a message on the provided channel.
    /// MessageSender is stamped with this component's owner if not already set.
    /// </summary>
    /// <param name="MessageChannel">The gameplay tag channel to broadcast on.</param>
    /// <param name="Message">The message struct to broadcast.</param>
	template<typename FMessageType>
	void BroadcastMessage(FGameplayTag MessageChannel, FMessageType Message)
	{
		if (Controller) Controller->BroadcastMessage(MessageChannel, MoveTemp(Message));
	}

	/// <summary>
	/// Broadcasts a message on the instanced channel for a specific target actor.
	/// Only listeners that called ListenForMessageFromContext with the same BaseTag
	/// on a controller whose ContextObject matches TargetObject will receive the message.
	/// </summary>
	/// <param name="BaseTag">The base gameplay tag used to derive the instanced channel.</param>
	/// <param name="TargetObject">The actor that identifies the instanced channel to broadcast on.</param>
	/// <param name="Message">The message struct to broadcast.</param>
	template<typename FMessageType>
	void BroadcastMessageToObject(FGameplayTag BaseTag, AActor* TargetObject, FMessageType Message)
	{
		if (Controller) Controller->BroadcastMessageToObject(BaseTag, TargetObject, MoveTemp(Message));
	}

	/// <summary>
	/// Registers a listener for messages of the given type on the provided channel.
	/// The handle is stored internally and cleaned up automatically on EndPlay.
	/// </summary>
	/// <param name="MessageChannel">The gameplay tag channel to listen on.</param>
	/// <param name="Callback">The function to invoke when a matching message is received.</param>
	template<typename FMessageType>
	FGameplayMessageListenerHandle ListenForMessage(FGameplayTag MessageChannel, TFunction<void(FGameplayTag, const FMessageType&)> Callback)
	{
		return Controller
			? Controller->ListenForMessage<FMessageType>(MessageChannel, MoveTemp(Callback))
			: FGameplayMessageListenerHandle();
	}

	/// <summary>
	/// Registers a listener on the instanced channel derived from this component's owning actor.
	/// Only receives messages broadcast via BroadcastMessageToObject targeting the same actor.
	/// </summary>
	/// <param name="BaseTag">The base gameplay tag used to derive the instanced channel.</param>
	/// <param name="Callback">The function to invoke when a matching message is received.</param>
	template<typename FMessageType>
	FGameplayMessageListenerHandle ListenForMessageFromContext(FGameplayTag BaseTag, TFunction<void(FGameplayTag, const FMessageType&)> Callback)
	{
		return Controller
			? Controller->ListenForMessageFromContext<FMessageType>(BaseTag, MoveTemp(Callback))
			: FGameplayMessageListenerHandle();
	}

	/// <summary>
	/// Registers a listener on a channel that filters incoming messages to only those
	/// where MessageReceiver matches the provided object.
	/// Requires FMessageType to derive from FPericulumMessage.
	/// </summary>
	/// <param name="MessageChannel">The gameplay tag channel to listen on.</param>
	/// <param name="ReceiverFilter">The UObject that MessageReceiver must match for the callback to fire.</param>
	/// <param name="Callback">The function to invoke when a matching message is received.</param>
	template<typename FMessageType>
	FGameplayMessageListenerHandle ListenForMessageTargetingObject(FGameplayTag MessageChannel, UObject* ReceiverFilter, TFunction<void(FGameplayTag, const FMessageType&)> Callback)
	{
		return Controller
			? Controller->ListenForMessageTargetingObject<FMessageType>(
				MessageChannel, ReceiverFilter, MoveTemp(Callback))
			: FGameplayMessageListenerHandle();
	}

	/// <summary>
	/// Registers a listener on a channel that filters incoming messages to only those
	/// where MessageSender matches the provided object.
	/// Requires FMessageType to derive from FPericulumMessage.
	/// </summary>
	/// <param name="MessageChannel">The gameplay tag channel to listen on.</param>
	/// <param name="SenderFilter">The UObject that MessageSender must match for the callback to fire.</param>
	/// <param name="Callback">The function to invoke when a matching message is received.</param>
	template<typename FMessageType>
	FGameplayMessageListenerHandle ListenForMessageFromObject(FGameplayTag MessageChannel, UObject* SenderFilter, TFunction<void(FGameplayTag, const FMessageType&)> Callback)
	{
		return Controller
			? Controller->ListenForMessageFromObject<FMessageType>(
				MessageChannel, SenderFilter, MoveTemp(Callback))
			: FGameplayMessageListenerHandle();
	}

private:
	/// <summary>
	/// The messaging controller owned by this component.
	/// Created in BeginPlay with the owning actor as both the outer and the context object.
	/// </summary>
	UPROPERTY()
	TObjectPtr<UMessagingController> Controller;
};
