#pragma once

/// @file CodeGameInstance.h
/// @brief Defines the UCodeGameInstance class, which serves as the base game instance for the Periculum game.

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CodeGameInstance.generated.h"

/**
 * Defines the base game instance class for the Periculum game. It manages level loading, input device management, and other global game state information.
 */
UCLASS()
class PERICULUM_API UCodeGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

public:
#pragma region Level Management
	/// <summary>
	/// Loads a level safely by its index in the GameLevels array. If the index is invalid, it will not attempt to load the level.
	/// </summary>
	/// <param name="LevelIndex">The index of the level to load.</param>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadLevelSafe(int LevelIndex);

	/// <summary>
	/// Loads a level safely by its index in the GameLevels array after a specified delay. If the index is invalid, it will not attempt to load the level.
	/// </summary>
	/// <param name="LevelIndex">The index of the level to load.</param>
	/// <param name="Delay">The delay before loading the level.</param>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadLevelSafeDelayed(int LevelIndex, float Delay = 0.5f);


	/// <summary>
	/// Loads the main menu level. This function is intended to be called when the player wants to return to the main menu.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadMainMenu();

	/// <summary>
	/// Loads the main menu level after a specified delay. This function is intended to be called when the player wants to return to the main menu.
	/// </summary>
	/// <param name="Delay">The delay before loading the level.</param>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadMainMenuDelayed(float Delay = 0.5f);

	/// <summary>
	/// Loads the first level of the game. This function is intended to be called when starting a new game.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadFirstLevel();

	/// <summary>
	/// Loads the first level of the game after a specified delay. This function is intended to be called when starting a new game.
	/// </summary>
	/// <param name="Delay">The delay before loading the level.</param>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadFirstLevelDelayed(float Delay = 0.5f);

	/// <summary>
	/// Loads the gym level of the game. This function is intended to be called when the player wants to access the gym area.
	/// The Gym level is used for training and practice within the game, providing a controlled environment for players to improve their skills.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadGymLevel();

	/// <summary>
	/// Loads the gym level of the game after a specified delay. This function is intended to be called when the player wants to access the gym area.
	/// </summary>
	/// <param name="Delay">The delay before loading the level.</param>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadGymLevelDelayed(float Delay = 0.5f);

	/// <summary>
	/// Loads the museum level of the game. This function is intended to be called when the player wants to access the museum area.
	/// The Museum level is used for showcasing achievements, collectibles, and other in-game content that the player has access to throughout their journey.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadMuseumLevel();

	/// <summary>
	/// Loads the museum level of the game after a specified delay. This function is intended to be called when the player wants to access the museum area.
	/// </summary>
	/// <param name="Delay">The delay before loading the level.</param>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadMuseumLevelDelayed(float Delay = 0.5f);

	/// <summary>
	/// Restarts the current level. This function is intended to be called when the player wants to restart the level they are currently in, resetting all progress and state within that level.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void RestartCurrentLevel();

	/// <summary>
	/// Restarts the current level after a specified delay. This function is intended to be called when the player wants to restart the level they are currently in, resetting all progress and state within that level.
	/// </summary>
	/// <param name="Delay">The delay before restarting the level.</param>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void RestartCurrentLevelDelayed(float Delay = 0.5f);

	/// <summary>
	/// Grabs the name of the current level based on the CurrentLevelIndex. If the index is invalid, it returns "InvalidLevel".
	/// </summary>
	/// <returns>The name of the current level.</returns>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	FORCEINLINE FName GetCurrentLevelName() const { return GameLevels.IsValidIndex(CurrentLevelIndex) ? GameLevels[CurrentLevelIndex] : FName(TEXT("InvalidLevel")); }

	/// <summary>
	/// Grabs the index of the current level. This index corresponds to the position of the level in the GameLevels array.
	/// </summary>
	/// <returns>The index of the current level.</returns>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	FORCEINLINE int GetCurrentLevelIndex() const { return CurrentLevelIndex; }

	/// <summary>
	/// Grabs the total number of levels defined in the GameLevels array. This can be used to determine how many levels are available in the game.
	/// </summary>
	/// <returns>The total number of levels.</returns>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	FORCEINLINE int GetTotalLevels() const { return GameLevels.Num(); }

	/// <summary>
	/// Grabs all the level names defined in the GameLevels array. This can be used to display a list of available levels or for other game logic that requires knowledge of all levels.
	/// </summary>
	/// <returns>An array of all level names.</returns>
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	FORCEINLINE TArray<FName> GetAllLevelNames() const { TArray<FName> LevelNames = GameLevels; return LevelNames; }
#pragma endregion

#pragma region Input Device Management
	/// <summary>
	/// Grabs the current input device type being used by the player. This can be used to determine if the player is using a keyboard, mouse, gamepad, or other input device.
	/// </summary>
	/// <returns>The current input device type.</returns>
	UFUNCTION(BlueprintCallable, Category = "Controls")
	FORCEINLINE EInputDeviceType GetCurrentInputDeviceType() const { return CurrentInputDeviceType; }

	/// <summary>
	/// Sets the current input device type being used by the player. This can be used to update the game's input handling logic based on the player's preferred input method.
	/// </summary>
	/// <param name="NewInputDeviceType">The new input device type to set.</param>
	UFUNCTION(BlueprintCallable, Category = "Controls")
	void SetCurrentInputDeviceType(EInputDeviceType NewInputDeviceType);

	/// <summary>
	/// Grabs the preferred gamepad type for the player. This can be used to determine which type of gamepad the player prefers to use, allowing for customized input handling and UI prompts.
	/// </summary>
	/// <returns>The preferred gamepad type.</returns>
	UFUNCTION(BlueprintCallable, Category = "Controls")
	FORCEINLINE EInputDeviceType GetPreferredGamepadType() const { return PreferredGamepadType; }

	/// <summary>
	/// Sets the preferred gamepad type for the player. This can be used to update the game's input handling logic and UI prompts based on the player's preferred gamepad type.
	/// </summary>
	/// <param name="NewPreferredGamepadType">The new preferred gamepad type to set.</param>
	UFUNCTION(BlueprintCallable, Category = "Controls")
	FORCEINLINE void SetPreferredGamepadType(EInputDeviceType NewPreferredGamepadType) { PreferredGamepadType = NewPreferredGamepadType; }
#pragma endregion

protected:
	/// <summary>
	/// The array of level names that are defined for the game. This array is used to manage level loading and to provide a list of available levels for the player.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance")
	TArray<FName> GameLevels;

	/// <summary>
	/// The index of the current level being played. This index corresponds to the position of the level in the GameLevels array and is used for level management and loading.
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Instance")
	int CurrentLevelIndex;

	/// <summary>
	/// The current input device type being used by the player. This can be used to determine if the player is using a keyboard, mouse, gamepad, or other input device, allowing for customized input handling and UI prompts.
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	EInputDeviceType CurrentInputDeviceType;

	/// <summary>
	/// The preferred gamepad type for the player. This can be used to determine which type of gamepad the player prefers to use, allowing for customized input handling and UI prompts.
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	EInputDeviceType PreferredGamepadType;

	/// <summary>
	/// Timer handle used for delayed level loading. This handle is used to manage the timing of level transitions, allowing for a delay before loading a new level or restarting the current level.
	/// </summary>
	UPROPERTY()
	FTimerHandle DelayedLevelLoadTimerHandle;
};
