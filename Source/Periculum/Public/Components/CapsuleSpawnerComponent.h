#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utility/CapsuleComponentUtilities.h"
#include "CapsuleSpawnerComponent.generated.h"

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

private:
	FVector LastSpawnLocation;
};
