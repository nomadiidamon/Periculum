// Fill out your copyright notice in the Description page of Project Settings.

/// @file GameStateTags.h
/// @brief This header file defines a variety of Gameplay Tags relating to Game States used throughout the Periculum project.

#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"


/// @defgroup GameStateTags Game State Tags
/// @{
/// Basic state tag for general use.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State);
/// Represents an active state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Active);
/// Represents a living state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Alive);
/// Represents a dead state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Dead);
/// Represents a busy state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Busy);


/// @defgroup MovementStates Movement States
/// @{
/// Represents a movement state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement);
/// Represents a grounded movement state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Grounded);
/// Represents a falling movement state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Falling);
/// Represents a flying movement state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Flying);
/// Represents a hovering movement state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Hovering);
/// Represents a grappling movement state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Grappling);
/// Represents a climbing movement state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Climbing);
/// @}


/// @defgroup InteractionStates Interaction States
/// @{
/// Represents an interaction state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Interaction);
/// Represents an interacting state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Interaction_Interacting);
/// Represents a disabled interaction state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Interaction_Disabled);
/// @}


/// @}