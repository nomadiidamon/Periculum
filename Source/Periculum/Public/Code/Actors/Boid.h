#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Code/Components/FlockingComponent.h"
#include "Boid.generated.h"

//class UFlockingComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class USphereComponent;
class UTraceComponent;
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
	UFUNCTION()
	bool HasFlockingComponent() const { return FlockingComponent != nullptr; }
	UFUNCTION()
	void UpdateFlockSettings(const FFlockSettings& NewSettings);
	FVector GetFlockingVelocity() const;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<UFlockingComponent> FlockingComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	//TObjectPtr<UTraceComponent> TraceComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	bool bDrawDebugRadius = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	bool bDrawDebugSightLine = false;

public:
};
