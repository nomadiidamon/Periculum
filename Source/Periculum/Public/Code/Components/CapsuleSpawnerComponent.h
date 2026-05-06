#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Code/Utility/SpawnModes.h"
#include "CapsuleSpawnerComponent.generated.h"


USTRUCT(BlueprintType)
struct FCapsuleSpawnParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	ESpawnLocationMode LocationMode = ESpawnLocationMode::InsideCapsule;

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

class UCapsuleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERICULUM_API UCapsuleSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCapsuleSpawnerComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnRegister() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	FCapsuleSpawnParams SpawnParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	TArray<FCapsuleSpawnData> SpawnHistory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	int32 MaxSpawnHistory = 100;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	int32 RandomSeed = 0;

	FRandomStream RandomStream;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	bool bDebugDrawArea = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capsule Spawning")
	bool bDebugDrawLastPoint = true;

public:
	UFUNCTION(BlueprintCallable, Category = "Capsule Spawning")
	void SetSpawnParams(const FCapsuleSpawnParams& InParams) { SpawnParams = InParams; }

	UFUNCTION(BlueprintCallable, Category = "Capsule Spawning")
	void ClearSpawnHistory() { SpawnHistory.Empty(); }

	UFUNCTION(BlueprintCallable, Category = "Capsule Spawning")
	void SetRandomSeed(int32 InSeed) { RandomSeed = InSeed; RandomStream.Initialize(RandomSeed); }

	UFUNCTION(BlueprintCallable, Category = "Capsule Spawning")
	void DrawDebugSpawnArea() const;

	UFUNCTION(BlueprintCallable, Category = "Capsule Spawning")
	void DrawDebugLastSpawnPoint() const;

	UFUNCTION(BlueprintCallable, Category = "Capsule Spawning")
	FCapsuleSpawnData GenerateSpawnData();
	UFUNCTION(BlueprintCallable, Category = "Capsule Spawning")
	FCapsuleSpawnData GenerateAndStoreSpawnData();

	/// Location
	FVector GetRandomPointInCapsule() const;
	FVector GetRandomPointOnCapsuleSurface() const;

	/// Direction
	FVector GetRandomRadialDirection() const;

	///Rotation
	FRotator GetRandomRotation() const;

	/// Scale
	FVector GetRandomUniformScale() const;
	FVector GetRandomNonUniformScale() const;

private:
	FVector LastSpawnLocation;
};
