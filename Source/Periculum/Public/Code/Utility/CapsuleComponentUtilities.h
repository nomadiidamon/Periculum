#pragma once

#include "CoreMinimal.h"
#include "Code/Utility/SpawnModes.h"

#include "CapsuleComponentUtilities.generated.h"

/**
 * 
 */

class UCapsuleComponent;

USTRUCT(BlueprintType)
struct FCapsuleSpawnParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	ESpawnLocationMode LocationMode = ESpawnLocationMode::InsideShape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	ESpawnRotationMode RotationMode = ESpawnRotationMode::RandomRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	ESpawnScaleMode ScaleMode = ESpawnScaleMode::Uniform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning", meta = (ClampMin = "0.0"))
	float MinUniformScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning", meta = (ClampMin = "0.0"))
	float MaxUniformScale = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	FVector MinNonUniformScale = FVector(0.5f, 0.5f, 0.5f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	FVector MaxNonUniformScale = FVector(1.5f, 1.5f, 1.5f);

	FCapsuleSpawnParams() = default;
};

USTRUCT(BlueprintType)
struct FCapsuleSpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	FTransform SpawnTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	FVector SpawnDirection;

	FCapsuleSpawnData()
		: SpawnTransform(FTransform::Identity)
		, SpawnDirection(FVector::ForwardVector)
	{
	}

	FCapsuleSpawnData(const FTransform& InTransform, const FVector& InDirection)
		: SpawnTransform(InTransform)
		, SpawnDirection(InDirection)
	{
	}

	FCapsuleSpawnData(const FVector& InLocation, const FRotator& InRotation, const FVector& InScale, const FVector& InDirection)
		: SpawnTransform(FTransform(InRotation, InLocation, InScale))
		, SpawnDirection(InDirection)
	{
	}

};


class PERICULUM_API CapsuleComponentUtilities
{
public:

	static FVector GetRandomPointInCapsule(const UCapsuleComponent* CapsuleComponent, FRandomStream& RandomStream);

	static FVector GetRandomPointOnCapsuleSurface(const UCapsuleComponent* CapsuleComponent, FRandomStream& RandomStream);

	static FVector GetRandomRadialDirection(const UCapsuleComponent* CapsuleComponent, FRandomStream& RandomStream);

	static FRotator GetRandomRotation(FRandomStream& RandomStream);

	static FVector GetRandomUniformScale(const FCapsuleSpawnParams& SpawnParams, FRandomStream& RandomStream);

	static FVector GetRandomNonUniformScale(const FCapsuleSpawnParams& SpawnParams, FRandomStream& RandomStream);
};
