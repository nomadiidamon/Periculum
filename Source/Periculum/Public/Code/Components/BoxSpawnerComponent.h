#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Code/Utility/BoxComponentUtilities.h"

#include "BoxSpawnerComponent.generated.h"

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

private:
	FVector LastSpawnLocation;
		
};
