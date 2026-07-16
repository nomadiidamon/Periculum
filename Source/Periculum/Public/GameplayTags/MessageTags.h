// Fill out your copyright notice in the Description page of Project Settings.

/// @file MessageTags.h
/// @brief This header file defines a variety of Gameplay Tags used for decoupled system messaging throughout the Periculum project. These tags facilitate communication between different systems and components, enabling a flexible and modular architecture.

#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"


/// @defgroup MessageTags Message Tags
/// @{
/// Basic message tag for general use.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message);


/// @defgroup DebugMessages Debug Messages
/// @{
/// Debug message tag for logging and debugging purposes.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Debug);
/// @}


/// @defgroup WorldMessages World Messages
/// @{
/// World message tag for events related to the game world, such as time, weather, and season changes.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_World);
/// World time changed message tag for notifying systems of changes in the in-game time.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_World_TimeChanged);
/// World weather changed message tag for notifying systems of changes in the in-game weather conditions.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_World_WeatherChanged);
/// World season changed message tag for notifying systems of changes in the in-game seasons.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_World_SeasonChanged);
/// @}


/// @defgroup AudioMessages Audio Messages
/// @{
/// Audio message tag for events related to in-game audio, such as sound effects and music.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Audio);
/// Audio play message tag for notifying systems to play a specific audio clip or sound effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Audio_Play);
/// Audio stop message tag for notifying systems to stop a specific audio clip or sound effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Audio_Stop);
/// Audio pause message tag for notifying systems to pause a specific audio clip or sound effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Audio_Pause);
/// Audio resume message tag for notifying systems to resume a specific audio clip or sound effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Audio_Resume);
/// @}


/// @defgroup UIMessages UI Messages
/// @{
/// UI message tag for events related to the user interface, such as health, stamina, and mana changes.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_UI);
/// UI health changed message tag for notifying systems of changes in the player's health.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_UI_HealthChanged);
/// UI stamina changed message tag for notifying systems of changes in the player's stamina.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_UI_StaminaChanged);
/// UI mana changed message tag for notifying systems of changes in the player's mana.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_UI_ManaChanged);
/// @}


/// @defgroup NotificationMessages
/// @{
/// Notification message tag for events related to in-game notifications, such as alerts, warnings, and messages to the player.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Notification);
/// @}


/// @}