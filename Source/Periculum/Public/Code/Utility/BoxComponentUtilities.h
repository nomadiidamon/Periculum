#pragma once

#include "CoreMinimal.h"
#include "Code/Utility/SpawnModes.h"

#include "BoxComponentUtilities.generated.h"

/**
 * 
 */

class UBoxComponent;

USTRUCT(BlueprintType)
struct FBoxSpawnParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	ESpawnLocationMode LocationMode = ESpawnLocationMode::InsideShape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	ESpawnRotationMode RotationMode = ESpawnRotationMode::RandomRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	ESpawnScaleMode ScaleMode = ESpawnScaleMode::Uniform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning", meta = (ClampMin = "0.0"))
	float MinUniformScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning", meta = (ClampMin = "0.0"))
	float MaxUniformScale = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	FVector MinNonUniformScale = FVector(0.5f, 0.5f, 0.5f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	FVector MaxNonUniformScale = FVector(1.5f, 1.5f, 1.5f);

	FBoxSpawnParams() = default;

};

USTRUCT(BlueprintType)
struct FBoxSpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	FTransform SpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	FVector SpawnDirection;


	FBoxSpawnData()
		: SpawnTransform(FTransform::Identity)
		, SpawnDirection(FVector::ForwardVector)

	{
	}

	FBoxSpawnData(const FTransform& InTransform, const FVector& InDirection)
		: SpawnTransform(InTransform)
		, SpawnDirection(InDirection)

	{
	}

	FBoxSpawnData(const FVector& InLocation, const FRotator& InRotation, const FVector& InScale, const FVector& InDirection)
		: SpawnTransform(FTransform(InRotation, InLocation, InScale))
		, SpawnDirection(InDirection)
	{
	}
};


class PERICULUM_API BoxComponentUtilities
{
public:

	static FVector GetRandomPointInBox(const UBoxComponent* BoxComponent, FRandomStream& RandomStream);

	static FVector GetRandomPointOnBoxSurface(const UBoxComponent* BoxComponent, FRandomStream& RandomStream);

	static FVector GetRandomRadialDirection(const UBoxComponent* BoxComponent, FRandomStream& RandomStream);

	static FRotator GetRandomRotation(FRandomStream& RandomStream);

	static FVector GetRandomUniformScale(const FBoxSpawnParams& SpawnParams, FRandomStream& RandomStream);

	static FVector GetRandomNonUniformScale(const FBoxSpawnParams& SpawnParams, FRandomStream& RandomStream);

};
