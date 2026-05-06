#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

class UFlockingComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
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

public:
	void UpdateFlockSettings(const FFlockSettings& NewSettings);

};
