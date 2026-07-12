// Fill out your copyright notice in the Description page of Project Settings.


#include "Defines/GameplayTags/EffectTags.h"


/// Gameplay Effects

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect, "Effect", "Basic effect tag for general use.");


/// Crowd Control Effects

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_CrowdControl, "Effect.CrowdControl", "Represents a crowd control effect.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_CrowdControl_Stunned, "Effect.CrowdControl.Stunned", "Represents a stunned crowd control effect.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_CrowdControl_Paralyzed, "Effect.CrowdControl.Paralyzed", "Represents a paralyzed crowd control effect.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_CrowdControl_Frozen, "Effect.CrowdControl.Frozen", "Represents a frozen crowd control effect.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_CrowdControl_Confused, "Effect.CrowdControl.Confused", "Represents a confused crowd control effect.");


/// Damage Over Time Effects

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_DamageOverTime, "Effect.DamageOverTime", "Represents a damage over time effect.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_DamageOverTime_Poisoned, "Effect.DamageOverTime.Poisoned", "Represents a poisoned damage over time effect.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_DamageOverTime_Burning, "Effect.DamageOverTime.Burning", "Represents a burning damage over time effect.");


/// Buff Effects 

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_Buff, "Effect.Buff", "Represents a buff effect.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_Buff_Invulnerable, "Effect.Buff.Invulnerable", "Represents an invulnerable buff effect.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_Buff_Hidden, "Effect.Buff.Hidden", "Represents a hidden buff effect.");


/// Debuff Effects

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_Debuff, "Effect.Debuff", "Represents a debuff effect.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_Debuff_Weakened, "Effect.Debuff.Weakened", "Represents a weakened debuff effect.");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_Debuff_Slowed, "Effect.Debuff.Slowed", "Represents a slowed debuff effect.");
