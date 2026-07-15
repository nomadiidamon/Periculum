// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTags/InteractionTags.h"

/// Interaction Tags

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Interaction, "Interaction", "Basic interaction tag for general use.");


/// Interaction Types

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Interaction_Type, "Interaction.Type", "Represents an interaction type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Interaction_Type_Pickup, "Interaction.Type.Pickup", "Represents a pickup interaction type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Interaction_Type_Door, "Interaction.Type.Door", "Represents a door interaction type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Interaction_Type_NPC, "Interaction.Type.NPC", "Represents an NPC interaction type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Interaction_Type_Loot, "Interaction.Type.Loot", "Represents a loot interaction type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Interaction_Type_Examine, "Interaction.Type.Examine", "Represents an examine interaction type.");


/// Interaction Requirements

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Interaction_Requirement, "Interaction.Requirement", "Represents an interaction requirement.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Interaction_Requirement_Key, "Interaction.Requirement.Key", "Represents a key requirement for interaction.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Interaction_Requirement_Level, "Interaction.Requirement.Level", "Represents a level requirement for interaction.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Interaction_Requirement_Item, "Interaction.Requirement.Item", "Represents an item requirement for interaction.");
