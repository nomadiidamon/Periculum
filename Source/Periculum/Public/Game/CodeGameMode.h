#pragma once

/// @file CodeGameMode.h
/// @brief Defines the ACodeGameMode class, which serves as the base game mode for the Periculum game.

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CodeGameMode.generated.h"

/**
 * The base game mode class for the Periculum game. It defines the default behavior and rules for the game, including player spawning, game state management, and other core gameplay mechanics.
 */
UCLASS()
class PERICULUM_API ACodeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACodeGameMode();
};
