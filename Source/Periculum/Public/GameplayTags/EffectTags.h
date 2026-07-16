// Fill out your copyright notice in the Description page of Project Settings.

/// @file EffectTags.h
/// @brief This header file defines a variety of Gameplay Tags relating to GameplayEffects for GAS used throughout the Periculum project.

#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"


/// @defgroup EffectTags Effect Tags
/// @{
/// Basic effect tag for general use.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect);


/// @defgroup CrowdControlEffects Crowd Control Effects
/// @{
/// Represents a crowd control effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_CrowdControl);
/// Represents a stunned crowd control effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_CrowdControl_Stunned);
/// Represents a paralyzed crowd control effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_CrowdControl_Paralyzed);
/// Represents a frozen crowd control effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_CrowdControl_Frozen);
/// Represents a confused crowd control effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_CrowdControl_Confused);
/// @}


/// @defgroup DamageOverTimeEffects Damage Over Time Effects
/// @{
/// Represents a damage over time effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_DamageOverTime);
/// Represents a poisoned damage over time effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_DamageOverTime_Poisoned);
/// Represents a burning damage over time effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_DamageOverTime_Burning);
/// @}


/// @defgroup BuffEffects Buff Effects
/// @{
/// Represents a buff effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Buff);
/// Represents an invulnerable buff effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Buff_Invulnerable);
/// Represents a hidden buff effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Buff_Hidden);
/// @}


/// @defgroup DebuffEffects Debuff Effects
/// @{
/// Represents a debuff effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Debuff);
/// Represents a weakened debuff effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Debuff_Weakened);
/// Represents a slowed debuff effect.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Debuff_Slowed);
/// @}


/// @}