// Fill out your copyright notice in the Description page of Project Settings.


#include "Defines/GameplayTags/WeaponTags.h"


/// Weapon Tags

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon, "Weapon", "Basic weapon tag for general use.");


/// Weapon States

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_State, "Weapon.State", "Represents a weapon state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_State_Equipped, "Weapon.State.Equipped", "Represents an equipped weapon state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_State_Stowed, "Weapon.State.Stowed", "Represents a stowed weapon state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_State_Attacking, "Weapon.State.Attacking", "Represents an attacking weapon state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_State_Firing, "Weapon.State.Firing", "Represents a firing weapon state.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_State_Reloading, "Weapon.State.Reloading", "Represents a reloading weapon state.");


/// Weapon Condition

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Condition, "Weapon.Condition", "Represents a weapon condition.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Condition_Pristine, "Weapon.Condition.Pristine", "Represents a pristine weapon condition.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Condition_Damaged, "Weapon.Condition.Damaged", "Represents a damaged weapon condition.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Condition_Irreparable, "Weapon.Condition.Irreparable", "Represents an irreparable weapon condition.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Condition_Overheated, "Weapon.Condition.Overheated", "Represents an overheated weapon condition.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Condition_Jammed, "Weapon.Condition.Jammed", "Represents a jammed weapon condition.");


/// Weapon Rarity

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Rarity_Common, "Weapon.Rarity.Common", "Represents a common weapon rarity.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Rarity_Uncommon, "Weapon.Rarity.Uncommon", "Represents an uncommon weapon rarity.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Rarity_Rare, "Weapon.Rarity.Rare", "Represents a rare weapon rarity.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Rarity_Epic, "Weapon.Rarity.Epic", "Represents an epic weapon rarity.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Rarity_Legendary, "Weapon.Rarity.Legendary", "Represents a legendary weapon rarity.");


/// Weapon Parts

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Part, "Weapon.Part", "Represents a weapon part.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Part_Ranged, "Weapon.Part.Ranged", "Represents a ranged weapon part.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Part_Melee, "Weapon.Part.Melee", "Represents a melee weapon part.");


/// Ranged Weapon Parts

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Part_Ranged_Barrel, "Weapon.Part.Ranged.Barrel", "Represents a ranged weapon barrel part.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Part_Ranged_Scope, "Weapon.Part.Ranged.Scope", "Represents a ranged weapon scope part.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Part_Ranged_Stock, "Weapon.Part.Ranged.Stock", "Represents a ranged weapon stock part.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Part_Ranged_Magazine, "Weapon.Part.Ranged.Magazine", "Represents a ranged weapon magazine part.");


/// Melee Weapon Parts

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Part_Melee_Blade, "Weapon.Part.Melee.Blade", "Represents a melee weapon blade part.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Part_Melee_Hilt, "Weapon.Part.Melee.Hilt", "Represents a melee weapon hilt part.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Part_Melee_Crossguard, "Weapon.Part.Melee.Crossguard", "Represents a melee weapon crossguard part.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Part_Melee_Pommel, "Weapon.Part.Melee.Pommel", "Represents a melee weapon pommel part.");


/// Weapon Types

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type, "Weapon.Type", "Represents a weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Ranged, "Weapon.Type.Ranged", "Represents a ranged weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee, "Weapon.Type.Melee", "Represents a melee weapon type.");


/// One Handed Ranged Weapons

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Ranged_1H, "Weapon.Type.Ranged.1H", "Represents a one-handed ranged weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Ranged_1H_Pistol, "Weapon.Type.Ranged.1H.Pistol", "Represents a one-handed pistol weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Ranged_1H_ThrowingSpear, "Weapon.Type.Ranged.1H.ThrowingSpear", "Represents a one-handed throwing spear weapon type.");


/// Two Handed Ranged Weapons

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Ranged_2H, "Weapon.Type.Ranged.2H", "Represents a two-handed ranged weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Ranged_2H_Rifle, "Weapon.Type.Ranged.2H.Rifle", "Represents a two-handed rifle weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Ranged_2H_Crossbow, "Weapon.Type.Ranged.2H.Crossbow", "Represents a two-handed crossbow weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Ranged_2H_BowAndArrow, "Weapon.Type.Ranged.2H.BowAndArrow", "Represents a two-handed bow and arrow weapon type.");


/// One Handed Melee Weapons

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_1H, "Weapon.Type.Melee.1H", "Represents a one-handed melee weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_1H_Sword, "Weapon.Type.Melee.1H.Sword", "Represents a one-handed sword weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_1H_Axe, "Weapon.Type.Melee.1H.Axe", "Represents a one-handed axe weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_1H_Club, "Weapon.Type.Melee.1H.Club", "Represents a one-handed club weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_1H_Shield, "Weapon.Type.Melee.1H.Shield", "Represents a one-handed shield weapon type.");


/// Two Handed Melee Weapons

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_2H, "Weapon.Type.Melee.2H", "Represents a two-handed melee weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_2H_Sword, "Weapon.Type.Melee.2H.Sword", "Represents a two-handed sword weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_2H_Axe, "Weapon.Type.Melee.2H.Axe", "Represents a two-handed axe weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_2H_Club, "Weapon.Type.Melee.2H.Club", "Represents a two-handed club weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_2H_Shield, "Weapon.Type.Melee.2H.Shield", "Represents a two-handed shield weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_2H_Spear, "Weapon.Type.Melee.2H.Spear", "Represents a two-handed spear weapon type.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Weapon_Type_Melee_2H_Halberd, "Weapon.Type.Melee.2H.Halberd", "Represents a two-handed halberd weapon type.");