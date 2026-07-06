#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utility/SphereComponentUtilities.h"

#include "SphereSpawnerComponent.generated.h"

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

private:
	FVector LastSpawnLocation;
};
