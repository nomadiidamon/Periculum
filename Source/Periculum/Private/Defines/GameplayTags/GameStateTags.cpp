// Fill out your copyright notice in the Description page of Project Settings.


#include "Defines/GameplayTags/GameStateTags.h"


/// Basic States

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State, "State", "Basic state tag for general use.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Active, "State.Active", "Represents an active state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Alive, "State.Alive", "Represents a living state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Dead, "State.Dead", "Represents a dead state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Busy, "State.Busy", "Represents a busy state.");


/// Movement States

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Movement, "State.Movement", "Represents a movement state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Movement_Grounded, "State.Movement.Grounded", "Represents a grounded movement state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Movement_Falling, "State.Movement.Falling", "Represents a falling movement state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Movement_Flying, "State.Movement.Flying", "Represents a flying movement state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Movement_Hovering, "State.Movement.Hovering", "Represents a hovering movement state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Movement_Grappling, "State.Movement.Grappling", "Represents a grappling movement state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Movement_Climbing, "State.Movement.Climbing", "Represents a climbing movement state.");


/// Interaction States

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Interaction, "State.Interaction", "Represents an interaction state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Interaction_Interacting, "State.Interaction.Interacting", "Represents an interacting state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Interaction_Disabled, "State.Interaction.Disabled", "Represents a disabled interaction state.");
