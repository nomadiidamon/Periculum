// Fill out your copyright notice in the Description page of Project Settings.

/// @file WeaponTags.h
/// @brief This header file defines a variety of Gameplay Tags used in relation to weapons and their various classifications throughout the Periculum project. These tags facilitate the categorization and management of different weapon types, states, conditions, rarities, and parts.


#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"



/// @defgroup WeaponTags Weapon Tags
/// @{
/// Basic weapon tag for general use.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon);


/// @defgroup WeaponStates Weapon States
/// @{
/// Represents a weapon state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State);
/// Represents an equipped weapon state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State_Equipped);
/// Represents a stowed weapon state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State_Stowed);
/// Represents an attacking weapon state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State_Attacking);
/// Represents a firing weapon state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State_Firing);
/// Represents a reloading weapon state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State_Reloading);
/// @}


/// @defgroup WeaponConditions Weapon Conditions
/// @{
/// Represents a weapon condition.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition);
/// Represents a pristine weapon condition.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition_Pristine);
/// Represents a damaged weapon condition.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition_Damaged);
/// Represents an irreparable weapon condition.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition_Irreparable);
/// Represents an overheated weapon condition.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition_Overheated);
/// Represents a jammed weapon condition.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition_Jammed);
/// @}


/// @defgroup WeaponRarities Weapon Rarities
/// @{
/// Represents a common weapon rarity.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Rarity_Common);
/// Represents an uncommon weapon rarity.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Rarity_Uncommon);
/// Represents a rare weapon rarity.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Rarity_Rare);
/// Represents an epic weapon rarity.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Rarity_Epic);
/// Represents a legendary weapon rarity.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Rarity_Legendary);
/// @}


/// @defgroup WeaponParts Weapon Parts
/// @{
/// Represents a weapon part.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part);
/// Represents a ranged weapon part.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Ranged);
/// Represents a melee weapon part.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Melee);
/// @}


/// @defgroup RangedWeaponParts Ranged Weapon Parts
/// @{
/// Represents a ranged weapon barrel part.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Ranged_Barrel);
/// Represents a ranged weapon scope part.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Ranged_Scope);
/// Represents a ranged weapon stock part.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Ranged_Stock);
/// Represents a ranged weapon magazine part.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Ranged_Magazine);
/// @}


/// @defgroup MeleeWeaponParts Melee Weapon Parts
/// @{
/// Represents a melee weapon blade part.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Melee_Blade);
/// Represents a melee weapon hilt part.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Melee_Hilt);
/// Represents a melee weapon crossguard part.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Melee_Crossguard);
/// Represents a melee weapon pommel part.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Melee_Pommel);
/// @}


/// @defgroup WeaponTypes Weapon Types
/// @{
/// Represents a weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type);
/// Represents a ranged weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged);
/// Represents a melee weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee);
/// @}


/// @defgroup OneHandedRangedWeapons One Handed Ranged Weapons
/// @{
/// Represents a one-handed ranged weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_1H);
/// Represents a one-handed pistol weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_1H_Pistol);
/// Represents a one-handed throwing spear weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_1H_ThrowingSpear);
/// @}


/// @defgroup TwoHandedRangedWeapons Two Handed Ranged Weapons
/// @{
/// Represents a two-handed ranged weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_2H);
/// Represents a two-handed rifle weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_2H_Rifle);
/// Represents a two-handed crossbow weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_2H_Crossbow);
/// Represents a two-handed bow and arrow weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_2H_BowAndArrow);
/// @}


/// @defgroup OneHandedMeleeWeapons One Handed Melee Weapons
/// @{
/// Represents a one-handed melee weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_1H);
/// Represents a one-handed sword weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_1H_Sword);
/// Represents a one-handed axe weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_1H_Axe);
/// Represents a one-handed club weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_1H_Club);
/// Represents a one-handed shield weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_1H_Shield);
/// @}


/// @defgroup TwoHandedMeleeWeapons Two Handed Melee Weapons
/// @{
/// Represents a two-handed melee weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H);
/// Represents a two-handed sword weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Sword);
/// Represents a two-handed axe weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Axe);
/// Represents a two-handed club weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Club);
/// Represents a two-handed shield weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Shield);
/// Represents a two-handed spear weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Spear);
/// Represents a two-handed halberd weapon type.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Halberd);
/// @}


/// @}