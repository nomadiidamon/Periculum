// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PericulumMessage.generated.h"

/**
 * A basic message struct that can be used as a parent struct to define custom messages in the Periculum messaging system.
 */

USTRUCT(BlueprintType)
struct PERICULUM_API FPericulumMessage
{
	GENERATED_BODY()
	
	/// <summary>
	/// The UObject responsible for sending this message.
	/// If the message is sent through a UMessagingComponent, this value will be set to the owner of the component at the moment of sending.
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Periculum|Message")
	TWeakObjectPtr<UObject> MessageSender;

	/// <summary>
	/// The UObject that is intended to receive this message.
	/// This is used for when the message is intended for a specific recipient, and can be used to filter messages or provide context for the message's purpose.
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Periculum|Message")
	TWeakObjectPtr<UObject> MessageReceiver;

	/// <summary>
	/// When the message was sent, in seconds since the world began. This can be used for time-sensitive operations or logging.
	/// If the message is sent through a UMessagingComponent, this value will be set to the world time at the moment of sending by the component.
	/// If the message is sent from a non-world context, this value will be 0.0.
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Periculum|Message")
	double WorldTimeSeconds;

	/// <summary>
	/// An optional container of gameplay tags that can provide additional context for the message. This can be used to filter messages or provide metadata about the message's purpose or origin.
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Periculum|Message")
	FGameplayTagContainer ContextTags;
};
