// Fill out your copyright notice in the Description page of Project Settings.

/// @file InteractionTags.h
/// @brief This header file defines a variety of Gameplay Tags used to define interactions throughout the Periculum project.

#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"


/// @defgroup InteractionTags Interaction Tags
/// @{
/// Basic interaction tag for general use.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction);


/// @defgroup InteractionTypes Interaction Types
/// @{
/// Represents an interaction type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type);
/// Represents a pickup interaction type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type_Pickup);
/// Represents a door interaction type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type_Door);
/// Represents an NPC interaction type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type_NPC);
/// Represents a loot interaction type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type_Loot);
/// Represents an examine interaction type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Type_Examine);
/// @}


/// @defgroup InteractionRequirements Interaction Requirements
/// @{
/// Represents an interaction requirement.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Requirement);
/// Represents a key requirement for interaction.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Requirement_Key);
/// Represents a level requirement for interaction.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Requirement_Level);
/// Represents an item requirement for interaction.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interaction_Requirement_Item);
/// @}


/// @}