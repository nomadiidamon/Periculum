// Fill out your copyright notice in the Description page of Project Settings.


#include "Defines/GameplayTags/MessageTags.h"


/// Message Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message, "Message", "Basic message tag for general use.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_Debug, "Message.Debug", "Represents a debug message.");


/// World Message

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_World, "Message.World", "Represents a world message.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_World_TimeChanged, "Message.World.TimeChanged", "Represents a world time changed message.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_World_WeatherChanged, "Message.World.WeatherChanged", "Represents a world weather changed message.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_World_SeasonChanged, "Message.World.SeasonChanged", "Represents a world season changed message.");


/// Audio Messages

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_Audio, "Message.Audio", "Represents an audio message.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_Audio_Play, "Message.Audio.Play", "Represents an audio play message.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_Audio_Stop, "Message.Audio.Stop", "Represents an audio stop message.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_Audio_Pause, "Message.Audio.Pause", "Represents an audio pause message.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_Audio_Resume, "Message.Audio.Resume", "Represents an audio resume message.");


/// UI Messages

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_UI, "Message.UI", "Represents a UI message.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_UI_HealthChanged, "Message.UI.HealthChanged", "Represents a UI health changed message.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_UI_StaminaChanged, "Message.UI.StaminaChanged", "Represents a UI stamina changed message.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_UI_ManaChanged, "Message.UI.ManaChanged", "Represents a UI mana changed message.");


/// Notification Messages

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Message_Notification, "Message.Notification", "Represents a notification message.");

