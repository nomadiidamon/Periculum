// Fill out your copyright notice in the Description page of Project Settings.

/// @file AITags.h
/// @brief This header file defines a variety of Gameplay Tags used in relation to the state of AI.

#pragma once
#include "CoreMinimal.h"
#include "NativeGameplayTags.h"


/// @defgroup AITags AI Tags
/// @{


/// @defgroup AIBasicStates AI Basic States
/// @{
/// Represents an AI state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_AI);
/// Represents an AI alert state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_AI_Alert);
/// Represents an AI investigating state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_AI_Investigating);
/// Represents an AI combat state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_AI_Combat);
/// Represents an AI patrolling state.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_AI_Patrolling);
/// @}


/// @}