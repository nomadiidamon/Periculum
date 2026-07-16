// Fill out your copyright notice in the Description page of Project Settings.

/// @file EventTags.h
/// @brief Defines gameplay tags for various events in the Periculum project, including actor events, player events, interaction events, grapple events, weapon events, trace events, save/load events, crafting events, timer events, and time events.

#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"


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


/// @defgroup GrappleEvents Grapple Events
/// @{
/// Represents a grapple event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Grapple);
/// Represents a grapple started event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Grapple_Started);
/// Represents a grapple attached event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Grapple_Attached);
/// Represents a grapple detached event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Grapple_Detached);
/// Represents a grapple finished event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Grapple_Finished);
/// @}


/// @defgroup WeaponEvents Weapon Events
/// @{
/// Represents a weapon event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Weapon);
/// Represents a weapon reload started event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Weapon_ReloadStarted);
/// Represents a weapon reload finished event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Weapon_ReloadFinished);
/// Represents a weapon used event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Weapon_Used);
/// @}


/// @defgroup TraceEvents Trace Events
/// @{
/// Represents a trace event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Trace);
/// Represents a trace begin event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Trace_Begin);
/// Represents a trace end event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Trace_End);
/// Represents a trace hit event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Trace_Hit);
/// Represents a trace miss event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Trace_Miss);
/// @}


/// @defgroup SaveEvents Save Events
/// @{
/// Represents a save event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Save);
/// Represents a save started event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Save_Started);
/// Represents a save completed event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Save_Completed);
/// Represents a save failed event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Save_Failed);
/// @}


/// @defgroup LoadEvents Load Events
/// @{
/// Represents a load event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Load);
/// Represents a load started event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Load_Started);
/// Represents a load completed event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Load_Completed);
/// Represents a load failed event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Load_Failed);
/// @}


/// @defgroup CraftingEvents Crafting Events
/// @{
/// Represents a crafting event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Crafting);
/// Represents a crafting started event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Crafting_Started);
/// Represents a crafting completed event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Crafting_Completed);
/// Represents a crafting failed event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Crafting_Failed);
/// @}


/// @defgroup TimerEvents Timer Events
/// @{
/// Represents a timer event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Timer);
/// Represents a timer started event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Timer_Started);
/// Represents a timer completed event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Timer_Completed);
/// Represents a timer failed event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Timer_Failed);
/// @}


/// @defgroup TimeEvents Time Events
/// @{
/// Represents a time event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Time);
/// Represents a day started event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Time_DayStarted);
/// Represents a day ended event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Time_DayEnded);
/// Represents a night started event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Time_NightStarted);
/// Represents a night ended event
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Time_NightEnded);
/// @}

/// @}