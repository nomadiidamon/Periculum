#pragma once

#include "CoreMinimal.h"
#include "Code/Utility/SpawnModes.h"

#include "SphereComponentUtilities.generated.h"

/**
 *
 */

class USphereComponent;

USTRUCT(BlueprintType)
struct FSphereSpawnParams
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	ESpawnLocationMode LocationMode = ESpawnLocationMode::InsideShape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	ESpawnRotationMode RotationMode = ESpawnRotationMode::RandomRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	ESpawnScaleMode ScaleMode = ESpawnScaleMode::Uniform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning", meta = (ClampMin = "0.0"))
	float MinUniformScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning", meta = (ClampMin = "0.0"))
	float MaxUniformScale = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	FVector MinNonUniformScale = FVector(0.5f, 0.5f, 0.5f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	FVector MaxNonUniformScale = FVector(1.5f, 1.5f, 1.5f);

	FSphereSpawnParams() = default;

};

USTRUCT(BlueprintType)
struct FSphereSpawnData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	FTransform SpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	FVector SpawnDirection;


	FSphereSpawnData()
		: SpawnTransform(FTransform::Identity)
		, SpawnDirection(FVector::ForwardVector)

	{
	}

	FSphereSpawnData(const FTransform& InTransform, const FVector& InDirection)
		: SpawnTransform(InTransform)
		, SpawnDirection(InDirection)

	{
	}

	FSphereSpawnData(const FVector& InLocation, const FRotator& InRotation, const FVector& InScale, const FVector& InDirection)
		: SpawnTransform(FTransform(InRotation, InLocation, InScale))
		, SpawnDirection(InDirection)
	{
	}
};


class PERICULUM_API SphereComponentUtilities
{
public:

	static FVector GetRandomPointInSphere(const USphereComponent* SphereComponent, FRandomStream& RandomStream);

	static FVector GetRandomPointOnSphereSurface(const USphereComponent* SphereComponent, FRandomStream& RandomStream);

	static FVector GetRandomRadialDirection(const USphereComponent* SphereComponent, FRandomStream& RandomStream);

	static FRotator GetRandomRotation(FRandomStream& RandomStream);

	static FVector GetRandomUniformScale(const FSphereSpawnParams& SpawnParams, FRandomStream& RandomStream);

	static FVector GetRandomNonUniformScale(const FSphereSpawnParams& SpawnParams, FRandomStream& RandomStream);

};
