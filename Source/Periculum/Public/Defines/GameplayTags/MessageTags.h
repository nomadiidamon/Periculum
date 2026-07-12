// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 * This file defines a variety of Gameplay Tags used for deccoupled system messaging throughout the Periculum project. 
 */


/// Message Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Debug);

/// World Message
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_World);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_World_TimeChanged);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_World_WeatherChanged);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_World_SeasonChanged);

/// Audio Messages
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Audio);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Audio_Play);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Audio_Stop);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Audio_Pause);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Audio_Resume);

/// UI Messages
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_UI);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_UI_HealthChanged);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_UI_StaminaChanged);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_UI_ManaChanged);

/// Notification Messages
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Message_Notification);