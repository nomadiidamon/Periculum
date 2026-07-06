#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CodeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PERICULUM_API UCodeGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

public:
	/// Level Loading and Management
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadLevelSafe(int LevelIndex);

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadLevelSafeDelayed(int LevelIndex, float Delay = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadMainMenuDelayed(float Delay = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadFirstLevel();

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadFirstLevelDelayed(float Delay = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadGymLevel();

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadGymLevelDelayed(float Delay = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadMuseumLevel();

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void LoadMuseumLevelDelayed(float Delay = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void RestartCurrentLevel();

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void RestartCurrentLevelDelayed(float Delay = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	FORCEINLINE FName GetCurrentLevelName() const { return GameLevels.IsValidIndex(CurrentLevelIndex) ? GameLevels[CurrentLevelIndex] : FName(TEXT("InvalidLevel")); }

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	FORCEINLINE int GetCurrentLevelIndex() const { return CurrentLevelIndex; }

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	FORCEINLINE int GetTotalLevels() const { return GameLevels.Num(); }

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	FORCEINLINE TArray<FName> GetAllLevelNames() const { TArray<FName> LevelNames = GameLevels; return LevelNames; }


	/// Input Device Management
	UFUNCTION(BlueprintCallable, Category = "Controls")
	FORCEINLINE EInputDeviceType GetCurrentInputDeviceType() const { return CurrentInputDeviceType; }

	UFUNCTION(BlueprintCallable, Category = "Controls")
	void SetCurrentInputDeviceType(EInputDeviceType NewInputDeviceType);

	UFUNCTION(BlueprintCallable, Category = "Controls")
	FORCEINLINE EInputDeviceType GetPreferredGamepadType() const { return PreferredGamepadType; }

	UFUNCTION(BlueprintCallable, Category = "Controls")
	FORCEINLINE void SetPreferredGamepadType(EInputDeviceType NewPreferredGamepadType) { PreferredGamepadType = NewPreferredGamepadType; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance")
	TArray<FName> GameLevels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Instance")
	int CurrentLevelIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	EInputDeviceType CurrentInputDeviceType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	EInputDeviceType PreferredGamepadType;

	FTimerHandle DelayedLevelLoadTimerHandle;
};
