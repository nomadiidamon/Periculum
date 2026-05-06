#include "Code/Game/CodeGameInstance.h"

#include "Periculum/Periculum.h"

void UCodeGameInstance::Init()
{
	if (GameLevels.Num() == 0)
	{
		UE_LOG(GAME, Warning, TEXT("GameLevels array is empty in CodeGameInstance. Please populate it with the level names in the editor."));
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
		UE_LOG(GAME, Warning, TEXT("Invalid level index %d in LoadLevelSafe. Please check the GameLevels array in CodeGameInstance."), LevelIndex);
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
	UE_LOG(GAME, Log, TEXT("Loading Main Menu..."));
}

void UCodeGameInstance::LoadMainMenuDelayed(float Delay)
{
	GetWorld()->GetTimerManager().SetTimer(DelayedLevelLoadTimerHandle,
		FTimerDelegate::CreateUObject(this, &UCodeGameInstance::LoadMainMenu), Delay, false);
}

void UCodeGameInstance::LoadFirstLevel()
{
	UE_LOG(GAME, Log, TEXT("Loading First Level..."));
}

void UCodeGameInstance::LoadFirstLevelDelayed(float Delay)
{
	GetWorld()->GetTimerManager().SetTimer(DelayedLevelLoadTimerHandle,
		FTimerDelegate::CreateUObject(this, &UCodeGameInstance::LoadFirstLevel), Delay, false);
}

void UCodeGameInstance::LoadGymLevel()
{
	UE_LOG(GAME, Log, TEXT("Loading Gym Level..."));
}

void UCodeGameInstance::LoadGymLevelDelayed(float Delay)
{
	GetWorld()->GetTimerManager().SetTimer(DelayedLevelLoadTimerHandle,
		FTimerDelegate::CreateUObject(this, &UCodeGameInstance::LoadGymLevel), Delay, false);
}

void UCodeGameInstance::LoadMuseumLevel()
{
	UE_LOG(GAME, Log, TEXT("Loading Museum Level..."));
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
	UE_LOG(INPUT, Log, TEXT("Current input device type set to: %s"), *UEnum::GetValueAsString(CurrentInputDeviceType));
}


