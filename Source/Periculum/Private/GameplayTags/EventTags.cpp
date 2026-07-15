// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTags/EventTags.h"

/// Basic Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event, "Event", "Basic event tag for general use.");


/// Actor Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Actor, "Event.Actor", "Represents an actor event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Actor_Spawned, "Event.Actor.Spawned", "Represents an actor spawned event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Actor_Destroyed, "Event.Actor.Destroyed", "Represents an actor destroyed event.");


/// Player Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Player, "Event.Player", "Represents a player event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Player_Spawned, "Event.Player.Spawned", "Represents a player spawned event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Player_Died, "Event.Player.Died", "Represents a player died event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Player_Respawned, "Event.Player.Respawned", "Represents a player respawned event.");


/// Interaction Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Interaction, "Event.Interaction", "Represents an interaction event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Interaction_Started, "Event.Interaction.Started", "Represents an interaction started event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Interaction_Completed, "Event.Interaction.Completed", "Represents an interaction completed event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Interaction_Canceled, "Event.Interaction.Canceled", "Represents an interaction canceled event.");


/// Grapple Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Grapple, "Event.Grapple", "Represents a grapple event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Grapple_Started, "Event.Grapple.Started", "Represents a grapple started event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Grapple_Attached, "Event.Grapple.Attached", "Represents a grapple attached event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Grapple_Detached, "Event.Grapple.Detached", "Represents a grapple detached event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Grapple_Finished, "Event.Grapple.Finished", "Represents a grapple finished event.");


/// Weapon Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Weapon, "Event.Weapon", "Represents a weapon event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Weapon_ReloadStarted, "Event.Weapon.ReloadStarted", "Represents a weapon reload started event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Weapon_ReloadFinished, "Event.Weapon.ReloadFinished", "Represents a weapon reload finished event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Weapon_Used, "Event.Weapon.Used", "Represents a weapon used event.");


/// Trace Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Trace, "Event.Trace", "Represents a trace event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Trace_Begin, "Event.Trace.Begin", "Represents a trace begin event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Trace_End, "Event.Trace.End", "Represents a trace end event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Trace_Hit, "Event.Trace.Hit", "Represents a trace hit event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Trace_Miss, "Event.Trace.Miss", "Represents a trace miss event.");


/// Save Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Save, "Event.Save", "Represents a save event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Save_Started, "Event.Save.Started", "Represents a save started event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Save_Completed, "Event.Save.Completed", "Represents a save completed event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Save_Failed, "Event.Save.Failed", "Represents a save failed event.");


/// Load Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Load, "Event.Load", "Represents a load event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Load_Started, "Event.Load.Started", "Represents a load started event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Load_Completed, "Event.Load.Completed", "Represents a load completed event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Load_Failed, "Event.Load.Failed", "Represents a load failed event.");


/// Crafting Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Crafting, "Event.Crafting", "Represents a crafting event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Crafting_Started, "Event.Crafting.Started", "Represents a crafting started event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Crafting_Completed, "Event.Crafting.Completed", "Represents a crafting completed event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Crafting_Failed, "Event.Crafting.Failed", "Represents a crafting failed event.");


/// Timer Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Timer, "Event.Timer", "Represents a timer event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Timer_Started, "Event.Timer.Started", "Represents a timer started event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Timer_Completed, "Event.Timer.Completed", "Represents a timer completed event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Timer_Failed, "Event.Timer.Failed", "Represents a timer failed event.");


/// Time Events

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Time, "Event.Time", "Represents a time event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Time_DayStarted, "Event.Time.DayStarted", "Represents a day started event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Time_DayEnded, "Event.Time.DayEnded", "Represents a day ended event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Time_NightStarted, "Event.Time.NightStarted", "Represents a night started event.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Event_Time_NightEnded, "Event.Time.NightEnded", "Represents a night ended event.");
