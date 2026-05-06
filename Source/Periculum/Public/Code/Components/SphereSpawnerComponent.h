#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Code/Utility/SpawnModes.h"

#include "SphereSpawnerComponent.generated.h"

USTRUCT(BlueprintType)
struct FSphereSpawnParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	ESpawnLocationMode LocationMode = ESpawnLocationMode::InsideSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	ESpawnRotationMode RotationMode = ESpawnRotationMode::RandomRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	ESpawnScaleMode ScaleMode = ESpawnScaleMode::Uniform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning", meta=(ClampMin="0.0"))
	float MinUniformScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning", meta=(ClampMin="0.0"))
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

class USphereComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERICULUM_API USphereSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USphereSpawnerComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnRegister() override;
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	FSphereSpawnParams SpawnParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	TArray<FSphereSpawnData> SpawnHistory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	int32 MaxSpawnHistory = 100;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	int32 RandomSeed = 0;

	FRandomStream RandomStream;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	bool bDebugDrawArea = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Spawning")
	bool bDebugDrawLastPoint = true;

public:
	UFUNCTION(BlueprintCallable, Category = "Sphere Spawning")
	void SetSpawnParams(const FSphereSpawnParams& InParams) {  SpawnParams = InParams; }

	UFUNCTION(BlueprintCallable, Category = "Sphere Spawning")
	void ClearSpawnHistory() { SpawnHistory.Empty(); }

	UFUNCTION(BlueprintCallable, Category = "Sphere Spawning")
	void SetRandomSeed(int32 InSeed) { RandomSeed = InSeed; RandomStream.Initialize(RandomSeed); }

	UFUNCTION(BlueprintCallable, Category = "Sphere Spawning")
	void DrawDebugSpawnArea() const;

	UFUNCTION(BlueprintCallable, Category = "Sphere Spawning")
	void DrawDebugLastSpawnPoint() const;

	UFUNCTION(BlueprintCallable, Category = "Sphere Spawning")
	FSphereSpawnData GenerateSpawnData();
	
	UFUNCTION(BlueprintCallable, Category = "Sphere Spawning")
	FSphereSpawnData GenerateAndStoreSpawnData();

	/// Location
	FVector GetRandomPointInSphere() const;
	FVector GetRandomPointOnSphereSurface() const;

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
