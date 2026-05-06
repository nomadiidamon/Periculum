// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(GAME, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(GAMEPLAY, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HUD, Log, All);


DECLARE_LOG_CATEGORY_EXTERN(PLAYER, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(INPUT, Log, All);

DECLARE_LOG_CATEGORY_EXTERN(NPC, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ENEMY, Log, All);

DECLARE_LOG_CATEGORY_EXTERN(SFX, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(AUDIO, Log, All);

DECLARE_LOG_CATEGORY_EXTERN(ENVIRONMENT, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ITEM, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(WEAPON, Log, All);

UENUM(BlueprintType)
enum class EInputDeviceType : uint8
{
	IDT_Keyboard UMETA(DisplayName = "Keyboard"),
	IDT_PS5 UMETA(DisplayName = "PS5 Controller"),
	IDT_Xbox UMETA(DisplayName = "Xbox Controller"),
	IDT_Steam UMETA(DisplayName = "Steam Controller")
};