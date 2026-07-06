#pragma once

#include "CoreMinimal.h"
#include "SpawnModes.generated.h"


UENUM(BlueprintType)
enum class ESpawnScaleMode : uint8
{
    Uniform,
    NonUniform
};

UENUM(BlueprintType)
enum class ESpawnLocationMode : uint8
{
    InsideShape,
	OnShapeSurface
};

UENUM(BlueprintType)
enum class ESpawnRotationMode : uint8
{
    RandomRotation,
    AlignToDirection
};

UENUM(BlueprintType)
enum class ESpawnMode : uint8
{
    Sphere,
    Box,
    Capsule,
    Random,
    Custom
};