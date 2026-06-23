// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseSpawner.h"
#include "Code/Components/FlockingComponent.h"
#include "BoidFlock.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFlockSettingsChanged, const FFlockSettings&, NewSettings);

class ABoid;

UCLASS()
class PERICULUM_API ABoidFlock : public ABaseSpawner
{
	GENERATED_BODY()

public:
	ABoidFlock();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

public:
	FOnFlockSettingsChanged OnFlockSettingsChanged;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock")
	TSubclassOf<AActor> BoidClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FFlockSettings FlockSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Behavior")
	FFlockSettings LastFlockSettings;

public:
	UFUNCTION()
	void RegisterBoid(AActor* Boid);

	UFUNCTION()
	void SpawnBoids();

	UFUNCTION()
	TArray<AActor*> GetNeighboringBoids(AActor* Boid, float Radius) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock")
	TArray<AActor*> Boids;
	UFUNCTION()
	void UpdateBoidSettings(const FFlockSettings& NewSettings);
};
