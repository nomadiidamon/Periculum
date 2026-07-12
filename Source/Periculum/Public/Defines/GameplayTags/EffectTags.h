// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 * This file defines a variety of Gameplay Tags relating to GameplayEffects for GAS used throughout the Periculum project. 
 */


// Gameplay Effects
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_CrowdControl);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_CrowdControl_Stunned);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_CrowdControl_Paralyzed);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_CrowdControl_Frozen);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_CrowdControl_Confused);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_DamageOverTime);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_DamageOverTime_Poisoned);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_DamageOverTime_Burning);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Buff);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Buff_Invulnerable);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Buff_Hidden);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Debuff);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Debuff_Weakened);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Debuff_Slowed);
