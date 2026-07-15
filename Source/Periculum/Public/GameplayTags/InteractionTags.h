// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 * This file defines a variety of Gameplay Tags used to define interactions throughout the Periculum project. 
 */


/// Interaction Tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction);

/// Interaction Types
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type_Pickup);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type_Door);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type_NPC);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type_Loot);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type_Examine);

/// Interaction Requirments
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Requirement);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Requirement_Key);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Requirement_Level);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Requirement_Item);
