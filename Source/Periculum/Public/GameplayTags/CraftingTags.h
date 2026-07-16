// Fill out your copyright notice in the Description page of Project Settings.

/// @file CraftingTags.h
/// @brief This header file defines a variety of Gameplay Tags used in relation to crafting throughout the Periculum project.

#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"


/// @defgroup CraftingTags Crafting Tags
/// @{
/// Basic crafting tag for general use.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting);


/// @defgroup CraftingStations Crafting Station Tags
/// @{
/// Represents a crafting station.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Station);
/// Represents a smith crafting station.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Station_Smith);
/// Represents a chemist crafting station.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Station_Chemist);
/// Represents a mage crafting station.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Station_Mage);
/// @}


/// @defgroup CraftingRecipes Crafting Recipe Tags
/// @{
/// Represents a crafting recipe.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Recipe);
/// Represents a weapon crafting recipe.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Recipe_Weapon);
/// Represents an armor crafting recipe.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Recipe_Armor);
/// Represents an ability crafting recipe.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Recipe_Ability);
/// Represents a consumable crafting recipe.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Recipe_Consumable);
/// Represents a metal alloy crafting recipe.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Recipe_MetalAlloy);
/// @}


/// @defgroup CraftingResources Crafting Resource Tags
/// @{
/// Represents a crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource);
/// Represents a wood crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Wood);
/// Represents a cloth crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Cloth);
/// Represents a leather crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Leather);
/// Represents a clay crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Clay);
/// Represents a metal crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal);
/// Represents a gem crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Gem);
/// Represents a herb crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Herb);
/// @}


/// @defgroup MetalOres Crafting Resource Tags - Metal Ores
/// @{
/// Represents a metal ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore);
/// Represents an iron ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Iron);
/// Represents an aluminum ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Aluminum);
/// Represents a copper ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Copper);
/// Represents a zinc ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Zinc);
/// Represents a tin ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Tin);
/// Represents a lead ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Lead);
/// Represents a cobalt ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Cobalt);
/// Represents a silver ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Silver);
/// Represents a gold ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Gold);
/// Represents a platinum ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Platinum);
/// Represents a mercury ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Mercury);
/// Represents a palladium ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Palladium);
/// Represents a neodymium ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Neodymium);
/// Represents a titanium ore crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Ore_Titanium);
/// @}


/// @defgroup MetalAlloys Crafting Resource Tags - Metal Alloys
/// @{
/// Represents a metal alloy crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Alloy);
/// Represents a bronze alloy crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Alloy_Bronze);
/// Represents a brass alloy crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Alloy_Brass);
/// Represents a cast iron alloy crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Alloy_CastIron);
/// Represents a steel alloy crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Alloy_Steel);
/// Represents a stainless steel alloy crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Alloy_Steel_Stainless);
/// Represents an electrum alloy crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Alloy_Electrum);
/// Represents a gun metal alloy crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Alloy_GunMetal);
/// Represents a sterling silver alloy crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Alloy_SterlingSilver);
/// Represents a white gold alloy crafting resource.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crafting_Resource_Metal_Alloy_WhiteGold);
/// @}


/// @}