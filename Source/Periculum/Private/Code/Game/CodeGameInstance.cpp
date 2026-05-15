#include "Code/Game/CodeGameInstance.h"
#include "Code/Utility/PericulumLog.h"


void UCodeGameInstance::Init()
{
	if (GameLevels.Num() == 0)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "GameLevels array is empty in CodeGameInstance. Please populate it with the level names in the editor.");
	}
	else
	{
		CurrentLevelIndex = 0;
	}
	PreferredGamepadType = EInputDeviceType::IDT_PS5;
}

void UCodeGameInstance::LoadLevelSafe(int LevelIndex)
{
	if (!GameLevels.IsValidIndex(LevelIndex))
	{
		PERICULUM_LOG(Periculum_Game, Warning, "Invalid level index %d in LoadLevelSafe. Please check the GameLevels array in CodeGameInstance.", LevelIndex);
		return;
	}
	CurrentLevelIndex = LevelIndex;
	GEngine->SetClientTravel(GetWorld(), *GameLevels[CurrentLevelIndex].ToString(), TRAVEL_Absolute);
}

void UCodeGameInstance::LoadLevelSafeDelayed(int LevelIndex, float Delay)
{
	GetWorld()->GetTimerManager().SetTimer(DelayedLevelLoadTimerHandle,
		FTimerDelegate::CreateUObject(this, &UCodeGameInstance::LoadLevelSafe, LevelIndex), Delay, false);
}

void UCodeGameInstance::LoadMainMenu()
{
	PERICULUM_LOG(Periculum_Game, Log, "Loading Main Menu...");
}

void UCodeGameInstance::LoadMainMenuDelayed(float Delay)
{
	GetWorld()->GetTimerManager().SetTimer(DelayedLevelLoadTimerHandle,
		FTimerDelegate::CreateUObject(this, &UCodeGameInstance::LoadMainMenu), Delay, false);
}

void UCodeGameInstance::LoadFirstLevel()
{
	PERICULUM_LOG(Periculum_Game, Log, "Loading First Level...");
}

void UCodeGameInstance::LoadFirstLevelDelayed(float Delay)
{
	GetWorld()->GetTimerManager().SetTimer(DelayedLevelLoadTimerHandle,
		FTimerDelegate::CreateUObject(this, &UCodeGameInstance::LoadFirstLevel), Delay, false);
}

void UCodeGameInstance::LoadGymLevel()
{
	PERICULUM_LOG(Periculum_Game, Log, "Loading Gym Level...");
}

void UCodeGameInstance::LoadGymLevelDelayed(float Delay)
{
	GetWorld()->GetTimerManager().SetTimer(DelayedLevelLoadTimerHandle,
		FTimerDelegate::CreateUObject(this, &UCodeGameInstance::LoadGymLevel), Delay, false);
}

void UCodeGameInstance::LoadMuseumLevel()
{
	PERICULUM_LOG(Periculum_Game, Log, "Loading Museum Level...");
}

void UCodeGameInstance::LoadMuseumLevelDelayed(float Delay)
{
	GetWorld()->GetTimerManager().SetTimer(DelayedLevelLoadTimerHandle,
		FTimerDelegate::CreateUObject(this, &UCodeGameInstance::LoadMuseumLevel), Delay, false);
}

void UCodeGameInstance::RestartCurrentLevel()
{
	LoadLevelSafe(CurrentLevelIndex);
}

void UCodeGameInstance::RestartCurrentLevelDelayed(float Delay)
{
	GetWorld()->GetTimerManager().SetTimer(DelayedLevelLoadTimerHandle,
		FTimerDelegate::CreateUObject(this, &UCodeGameInstance::RestartCurrentLevel), Delay, false);
}

void UCodeGameInstance::SetCurrentInputDeviceType(EInputDeviceType NewInputDeviceType)
{
	if (NewInputDeviceType != EInputDeviceType::IDT_Keyboard) {
		CurrentInputDeviceType = PreferredGamepadType;
	}
	else
	{
		CurrentInputDeviceType = NewInputDeviceType;
	}
	PERICULUM_LOG(Periculum_Input, Log, "Current input device type set to: %s", *UEnum::GetValueAsString(CurrentInputDeviceType));
}


