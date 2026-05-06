// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Code/Utility/SpawnModes.h"

#include "BoxSpawnerComponent.generated.h"

USTRUCT(BlueprintType)
struct FBoxSpawnParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	ESpawnLocationMode LocationMode = ESpawnLocationMode::InsideBox;

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

class UBoxComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERICULUM_API UBoxSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBoxSpawnerComponent();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnRegister() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	FBoxSpawnParams SpawnParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	TArray<FBoxSpawnData> SpawnHistory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	int32 MaxSpawnHistory = 100;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	int32 RandomSeed = 0;

	FRandomStream RandomStream;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	bool bDebugDrawArea = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	bool bDebugDrawLastPoint = true;

public:
	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	void SetSpawnParams(const FBoxSpawnParams& InParams) { SpawnParams = InParams; }

	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	void ClearSpawnHistory() { SpawnHistory.Empty(); }

	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	void SetRandomSeed(int32 InSeed) { RandomSeed = InSeed; RandomStream.Initialize(RandomSeed); }

	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	void DrawDebugSpawnArea() const;

	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	void DrawDebugLastSpawnPoint() const;

	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	FBoxSpawnData GenerateSpawnData();
	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	FBoxSpawnData GenerateAndStoreSpawnData();

	/// Location
	FVector GetRandomPointInBox() const;
	FVector GetRandomPointOnBoxSurface() const;
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
