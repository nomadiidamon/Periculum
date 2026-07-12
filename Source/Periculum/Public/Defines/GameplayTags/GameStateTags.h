// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 * This file defines a variety of Gameplay Tags relating to Game States used throughout the Periculum Project.
 */


/// Basic States
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Active);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Alive);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Dead);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Busy);

/// Movement States
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Grounded);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Falling);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Flying);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Hovering);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Grappling);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Movement_Climbing);

/// Interaction States
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Interaction);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Interaction_Interacting);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Interaction_Disabled);
