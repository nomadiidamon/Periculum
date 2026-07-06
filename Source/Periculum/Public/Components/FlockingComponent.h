#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlockingComponent.generated.h"

class ABoidFlock;
class USphereComponent;

USTRUCT(BlueprintType)
struct FFlockSettings
{
	GENERATED_BODY()
public:
	/// Cohesion, Separation, Alignment weights and radii, the higher the weight, the more influence that behavior has on the boid's movement
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float CohesionWeight = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float CohesionRadius = 450.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float SeparationWeight = 2.25f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float SeparationRadius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float AlignmentWeight = 1.0f;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float AlignmentRadius = 850.0f;

	/// Speed, Wander strength, and other tuning settings for the boid's movement

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "200.0"))
	float MaxSpeed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "100.0"))
	float MinSpeed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "100.0"))
	float MaxWanderStrength = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "50.0"))
	float MinWanderStrength = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "200.0"))
	float MaxForce = 75.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float TurnSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FVector FlockCenter = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "100.0"))
	float FlockCenterStrength = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FVector FlockAttractionPoint = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "100.0"))
	float FlockAttractionPointStrength = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	bool bDrawDebugRadiusAverage = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	bool bDrawDebugSightLine = false;

	bool operator==(const FFlockSettings& Other) const
	{
		return FMath::IsNearlyEqual(CohesionWeight, Other.CohesionWeight) &&
			FMath::IsNearlyEqual(SeparationWeight, Other.SeparationWeight) &&
			FMath::IsNearlyEqual(AlignmentWeight, Other.AlignmentWeight) &&
			FMath::IsNearlyEqual(CohesionRadius, Other.CohesionRadius) &&
			FMath::IsNearlyEqual(SeparationRadius, Other.SeparationRadius) &&
			FMath::IsNearlyEqual(AlignmentRadius, Other.AlignmentRadius) &&
			FMath::IsNearlyEqual(MaxSpeed, Other.MaxSpeed) &&
			FMath::IsNearlyEqual(MinSpeed, Other.MinSpeed) &&
			FMath::IsNearlyEqual(MaxWanderStrength, Other.MaxWanderStrength)&&
			FMath::IsNearlyEqual(MinWanderStrength, Other.MinWanderStrength)&&
			FMath::IsNearlyEqual(MaxForce, Other.MaxForce)&&
			FMath::IsNearlyEqual(TurnSpeed, Other.TurnSpeed)&&
			FlockCenter.Equals(Other.FlockCenter)&&
			FMath::IsNearlyEqual(FlockCenterStrength, Other.FlockCenterStrength)&&
			FlockAttractionPoint.Equals(Other.FlockAttractionPoint)&&
			FMath::IsNearlyEqual(FlockAttractionPointStrength, Other.FlockAttractionPointStrength)&&
			bDrawDebugRadiusAverage == Other.bDrawDebugRadiusAverage&&
			bDrawDebugSightLine == Other.bDrawDebugSightLine;
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
	TObjectPtr<ABoidFlock> FlockManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<USphereComponent> OverlappingSphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TArray<TObjectPtr<AActor>> OverlappingActors;

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
	FVector CalculateSteeringForce_Boid(FVector Cohesion, FVector Separation, FVector Alignment);

	FVector CalculateWander();
	FVector CalculateFlockCenterAttraction();
	FVector CalculateFlockAttractionPoint();
	FVector CalculateSteeringForce_Tuning(FVector Wander, FVector FlockCenter, FVector FlockAttraction);

	void CalculateVelocity(FVector CurrentVelocity);

	UFUNCTION()
	void UpdateFlockSettings(const struct FFlockSettings& NewSettings);

	UFUNCTION()
	void DrawOverlapComponentBounds();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
