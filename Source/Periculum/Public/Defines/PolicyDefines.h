// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PolicyDefines.generated.h"

UENUM(BlueprintType)
enum class EPolicyStackPriority : uint8
{
	Low = 0 UMETA(DisplayName = "Low"),
	Standard = 25 UMETA(DisplayName = "Standard"),
	Medium = 50 UMETA(DisplayName = "Medium"),
	High = 75 UMETA(DisplayName = "High"),
	Extreme = 100 UMETA(DisplayName = "Extreme")
};