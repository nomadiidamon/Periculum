#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlockingComponent.generated.h"

class ABoid;
class ABoidFlock;
class USphereComponent;
class UTraceComponent;

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
	float SeparationWeight = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float SeparationRadius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float AlignmentWeight = 3.0f;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "50.0", ClampMax = "2000.0"))
	float AlignmentRadius = 850.0f;

	/// Speed, Wander strength, and other tuning settings for the boid's movement

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "10.0", ClampMax = "1000.0"))
	float MaxSpeed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float MinSpeed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float MaxWanderStrength = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "50.0"))
	float MinWanderStrength = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxForce = 75.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float TurnSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FVector FlockCenter = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float FlockCenterStrength = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FVector FlockAttractionPoint = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float FlockAttractionPointStrength = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float CollisionDetectionRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	bool bDrawDebugRadiusAverage = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	bool bDrawDebugSightLine = true;

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
			FMath::IsNearlyEqual(CollisionDetectionRadius, Other.CollisionDetectionRadius) &&
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	// A referencce to the BoidFlock that this boid belongs to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<ABoidFlock> FlockManager;

	// Sphere component used to detect overlapping actors for flocking behavior
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TObjectPtr<USphereComponent> OverlappingSphereComponent;

	// The list of actors that are currently overlapping with the OverlappingSphereComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TArray<TObjectPtr<AActor>> OverlappingActors;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	//TObjectPtr<UTraceComponent> TraceComponent;

	// The list of actors that are considered obstacles for the boid to avoid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	TArray<TObjectPtr<AActor>> ObstacleActors;

	// The current velocity of the boid, which is updated based on the flocking behavior and other factors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	FVector Velocity;

	// The current wander vector of the boid, which is used to add randomness to its movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	FVector WanderVector;

	// The current speed of the boid, which is clamped between the minimum and maximum speed defined in the flock settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	float CurrentSpeed = 50.f;

	// The flock settings that define the behavior of the boid, such as cohesion, separation, alignment, and other parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	FFlockSettings FlockSettings;

public:
	void SetFlockManager(ABoidFlock* Manager) { FlockManager = Manager; }

	FVector ExecuteBoidBehavior(TArray<AActor*> Neighbors);
	FVector CalculateCohesion(TArray<AActor*> Neighbors);
	FVector CalculateSeparation(TArray<AActor*> Neighbors);
	FVector CalculateAlignment(TArray<AActor*> Neighbors);
	FVector CalculateSteeringForce_Boid(FVector Cohesion, FVector Separation, FVector Alignment);

	FVector ExecuteTuningBehavior();
	FVector CalculateWander();
	FVector CalculateFlockCenterAttraction();
	FVector CalculateFlockAttractionPoint();
	FVector CalculateSteeringForce_Tuning(FVector Wander, FVector FlockCenter, FVector FlockAttraction);


	FVector PredictCollisions(TArray<AActor*> Actors, float DeltaTime);
	FVector PredictFuturePosition(float DeltaTime);
	FVector PredictNeighborPosition(ABoid* Neighbor, float DeltaTime);

	FVector CalculateObstacleDistance(AActor* Obstacle, float DeltaTime);
	FVector PredictObstacleCollision(AActor* Obstacle, float DeltaTime);
	FVector AvoidObstaclesCollisions(TArray<AActor*> Obstacles, float DeltaTime);


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
