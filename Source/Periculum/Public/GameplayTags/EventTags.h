// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/// @file EventTags.h
/// @brief Defines gameplay tags for various events in the Periculum project, including actor events, player events, interaction events, grapple events, weapon events, trace events, save/load events, crafting events, timer events, and time events.
/// @todo Finish assigning comments to all event tags. The comments should describe the purpose and context of each tag, providing clarity for developers using these tags in gameplay logic.


/// @defgroup EventTags Event Tags
/// @{
/// Basic event tag for general use.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event);


/// @defgroup ActorEvents Actor Events
/// @{
/// Represents an actor event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Actor);
/// Represents an actor spawned event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Actor_Spawned);
/// Represents an actor destroyed event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Actor_Destroyed);
/// @}


/// @defgroup PlayerEvents Player Events
/// @{
/// Represents a player event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Player);
/// Represents a player spawned event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Player_Spawned);
/// Represents a player died event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Player_Died);
/// Represents a player respawned event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Player_Respawned);
/// @}


/// @defgroup InteractionEvents Interaction Events
/// @{
/// Represents an interaction event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Interaction);
/// Represents an interaction started event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Interaction_Started);
/// Represents an interaction completed event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Interaction_Completed);
/// Represents an interaction canceled event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Interaction_Canceled);
/// @}


/// Grapple Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Grapple);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Grapple_Started);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Grapple_Attached);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Grapple_Detached);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Grapple_Finished);

/// Weapon Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Weapon);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Weapon_ReloadStarted);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Weapon_ReloadFinished);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Weapon_Used);

/// Trace Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Trace);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Trace_Begin);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Trace_End);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Trace_Hit);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Trace_Miss);

/// Save Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Save);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Save_Started);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Save_Completed);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Save_Failed);

/// Load Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Load);	
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Load_Started);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Load_Completed);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Load_Failed);

/// Crafting Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Crafting);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Crafting_Started);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Crafting_Completed);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Crafting_Failed);


/// Timer Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Timer);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Timer_Started);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Timer_Completed);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Timer_Failed);

/// Time Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Time);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Time_DayStarted);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Time_DayEnded);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Time_NightStarted);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Time_NightEnded);

/// @}