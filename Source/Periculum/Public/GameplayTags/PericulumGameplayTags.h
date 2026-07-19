// Fill out your copyright notice in the Description page of Project Settings.

/// @file PericulumGameplayTags.h
/// @brief This header file serves as a centralized reference for all GameplayTags used throughout the Periculum project. It includes various tag categories such as AI, Crafting, Effects, Events, Game States, Interactions, Messages, and Weapons.

#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "AITags.h"
#include "CraftingTags.h"
#include "EffectTags.h"
#include "EventTags.h"
#include "GameStateTags.h"
#include "InteractionTags.h"
#include "MessageTags.h"
#include "WeaponTags.h"


/// @defgroup ActorTags Actor Tags
/// @{
/// Basic actor tag for general use.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Actor);
/// Represents an actor that is an ally of the player.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Actor_Ally);
/// Represents an actor that is an enemy of the player.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Actor_Enemy);
/// Represents an actor that is neutral to the player.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Actor_Neutral);
/// @}