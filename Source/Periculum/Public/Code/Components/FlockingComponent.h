#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlockingComponent.generated.h"

class ABoidFlock;
class USphereComponent;

USTRUCT(BlueprintType)
struct FFlockSettings
{
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float CohesionWeight = 8.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float SeparationWeight = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float AlignmentWeight = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float SafeRadius = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "2000.0"))
	float MaxSpeed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "1000.0"))
	float MinSpeed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	bool bDrawDebug = false;

	bool operator==(const FFlockSettings& Other) const
	{
		return FMath::IsNearlyEqual(CohesionWeight, Other.CohesionWeight) &&
			FMath::IsNearlyEqual(SeparationWeight, Other.SeparationWeight) &&
			FMath::IsNearlyEqual(AlignmentWeight, Other.AlignmentWeight) &&
			FMath::IsNearlyEqual(SafeRadius, Other.SafeRadius) &&
			FMath::IsNearlyEqual(MaxSpeed, Other.MaxSpeed) &&
			FMath::IsNearlyEqual(MinSpeed, Other.MinSpeed);
	}

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERICULUM_API UFlockingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFlockingComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	ABoidFlock* FlockManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	USphereComponent* OverlappingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TArray<AActor*> OverlappingActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	float CurrentSpeed = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	FFlockSettings FlockSettings;

public:
	void SetFlockManager(ABoidFlock* Manager) { FlockManager = Manager; }

	FVector CalculateCohesion(TArray<AActor*> Neighbors);
	FVector CalculateSeparation(TArray<AActor*> Neighbors);
	FVector CalculateAlignment(TArray<AActor*> Neighbors);

	UFUNCTION()
	void UpdateFlockSettings(const struct FFlockSettings& NewSettings);

	UFUNCTION()
	void DrawOverlapComponentBounds();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
