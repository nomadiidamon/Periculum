// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

/**
 * This file defines a variety of Gameplay Tags used in relation to the state of AI. 
 */



/// AI Basic States
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_AI);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_AI_Alert);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_AI_Investigating);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_AI_Combat);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_AI_Patrolling);

