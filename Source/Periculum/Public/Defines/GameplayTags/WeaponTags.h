// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 * This file defines a variety of Gameplay Tags relating to weapons and their various classifications. 
 */


/// Weapon Tags
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon);

/// Weapon States
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State_Equipped);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State_Stowed);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State_Attacking);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State_Firing);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_State_Reloading);

/// Weapon Condition
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition_Pristine);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition_Damaged);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition_Irreparable);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition_Overheated);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Condition_Jammed);

/// Weapon Rarity
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Rarity_Common);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Rarity_Uncommon);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Rarity_Rare);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Rarity_Epic);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Rarity_Legendary);

/// Weapon Parts
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Ranged);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Melee);

/// Ranged Weapon Parts
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Ranged_Barrel);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Ranged_Scope);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Ranged_Stock);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Ranged_Magazine);

/// Melee Weapon Parts
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Melee_Blade);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Melee_Hilt);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Melee_Crossguard);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Part_Melee_Pommel);

/// Weapon Types
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee);

/// One Handed Ranged Weapons
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_1H);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_1H_Pistol);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_1H_ThrowingSpear);

/// Two Handed Ranged Weapons
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_2H);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_2H_Rifle);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_2H_Crossbow);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Ranged_2H_BowAndArrow);

/// One Handed Melee Weapons
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_1H);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_1H_Sword);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_1H_Axe);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_1H_Club);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_1H_Shield);

/// Two Handed Melee Weapons
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Sword);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Axe);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Club);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Shield);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Spear);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Weapon_Type_Melee_2H_Halberd);
