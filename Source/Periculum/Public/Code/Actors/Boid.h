#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

class UFlockingComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class USphereComponent;
struct FFlockSettings;

UCLASS()
class PERICULUM_API ABoid : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoid();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	UFlockingComponent* GetFlockingComponent() const { return FlockingComponent; }

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	UFlockingComponent* FlockingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	bool bDrawDebugRadius = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	bool bDrawDebugSightLine = false;

public:
	void UpdateFlockSettings(const FFlockSettings& NewSettings);

};
