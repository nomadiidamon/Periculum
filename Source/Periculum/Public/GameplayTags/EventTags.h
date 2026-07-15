// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 * This file defines a variety of Gameplay Tags relating to Events used throughout the Periculum project. 
 */


/// Actor Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Actor);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Actor_Spawned);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Actor_Destroyed);

/// Player Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Player);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Player_Spawned);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Player_Died);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Player_Respawned);

/// Interaction Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Interaction);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Interaction_Started);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Interaction_Completed);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Interaction_Canceled);

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
