#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utility/BoxComponentUtilities.h"

#include "BoxSpawnerComponent.generated.h"

class UBoxComponent;

/**
 * A component that spawns points within a box defined by a UBoxComponent. It allows for customizable spawn parameters, randomization, and debug visualization of the spawn area and last spawn point.
 */
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
	/// <summary>
	/// The UBoxComponent that defines the spawning area. The component will spawn points within the bounds of this box.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	TObjectPtr<UBoxComponent> BoxComponent;

	/// <summary>
	/// The parameters that define how points are spawned within the box. This includes location, rotation, and scale modes, as well as min/max values for scaling.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	FBoxSpawnParams SpawnParams;

	/// <summary>
	/// The history of spawned points, stored as an array of FBoxSpawnData. This allows for tracking and debugging of previously spawned points.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	TArray<FBoxSpawnData> SpawnHistory;

	/// <summary>
	/// The maximum number of spawn history entries to keep. When the limit is reached, older entries will be removed.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	int32 MaxSpawnHistory = 100;

	/// <summary>
	/// The seed for the random number generator used for spawning. Changing this value will result in different spawn patterns.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	int32 RandomSeed = 0;

	/// <summary>
	/// The random stream used for generating random values for spawning. It is initialized with the RandomSeed and can be used to ensure consistent randomization across runs.
	/// </summary>
	UPROPERTY()
	FRandomStream RandomStream;

	/// <summary>
	/// Whether or not to draw the debug representation of the spawn area. If true, the box will be visualized in the editor and during gameplay for debugging purposes.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	bool bDebugDrawArea = true;

	/// <summary>
	/// Whether or not to draw the debug representation of the last spawned point. If true, the last spawn point will be visualized in the editor and during gameplay for debugging purposes.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Spawning")
	bool bDebugDrawLastPoint = true;

public:
	/// <summary>
	/// Sets the spawn parameters for the box spawner. This allows for dynamic changes to how points are spawned within the box, including location, rotation, and scale modes.
	/// </summary>
	/// <param name="InParams">The new spawn parameters to set.</param>
	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	void SetSpawnParams(const FBoxSpawnParams& InParams) { SpawnParams = InParams; }

	/// <summary>
	/// Clears the spawn history, removing all previously stored spawn data. This can be useful for resetting the spawner or starting a new spawning session without retaining old data.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	void ClearSpawnHistory() { SpawnHistory.Empty(); }

	/// <summary>
	/// Sets the random seed for the random number generator used in spawning. This allows for reproducible spawn patterns by initializing the random stream with a specific seed.
	/// </summary>
	/// <param name="InSeed">The new random seed to set.</param>
	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	void SetRandomSeed(int32 InSeed) { RandomSeed = InSeed; RandomStream.Initialize(RandomSeed); }

	/// <summary>
	/// Draws the debug representation of the spawn area defined by the UBoxComponent. This is useful for visualizing the bounds within which points will be spawned, aiding in debugging and level design.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	void DrawDebugSpawnArea() const;

	/// <summary>
	/// Draws the debug representation of the last spawned point. This is useful for visualizing where the most recent spawn occurred, aiding in debugging and ensuring that spawning behavior is as expected.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	void DrawDebugLastSpawnPoint() const;

	/// <summary>
	/// Generates spawn data based on the current spawn parameters and the bounds of the UBoxComponent. This function calculates a random location, rotation, and scale for a new spawn point within the box.
	/// </summary>
	/// <returns>The generated spawn data.</returns>
	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	FBoxSpawnData GenerateSpawnData();

	/// <summary>
	/// Generates spawn data and stores it in the spawn history. This function combines the generation of new spawn data with the management of the spawn history, ensuring that the history does not exceed the maximum allowed entries.
	/// </summary>
	/// <returns>The generated spawn data.</returns>
	UFUNCTION(BlueprintCallable, Category = "Box Spawning")
	FBoxSpawnData GenerateAndStoreSpawnData();

private:
	/// <summary>
	/// The last spawn location generated by the spawner. This is used for debug visualization and can be accessed to determine where the most recent spawn occurred.
	/// </summary>
	FVector LastSpawnLocation;
		
};
