// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTypes.generated.h"

UENUM(BlueprintType)
enum class EInputDeviceType : uint8
{
	IDT_Keyboard UMETA(DisplayName = "Keyboard"),
	IDT_PS5 UMETA(DisplayName = "PS5 Controller"),
	IDT_Xbox UMETA(DisplayName = "Xbox Controller"),
	IDT_Steam UMETA(DisplayName = "Steam Controller")
};
