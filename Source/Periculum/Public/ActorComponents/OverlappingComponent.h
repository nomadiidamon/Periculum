// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OverlappingComponent.generated.h"

class UPrimitiveComponent;

/*
* UOverlappingComponent is a custom Actor Component that tracks overlapping actors using a specified collision primitive.
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERICULUM_API UOverlappingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOverlappingComponent();

protected:
	virtual void BeginPlay() override;

public:
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	/// <summary>
	/// The collision primitive that this component will use to detect overlapping actors. This should be set to a valid UPrimitiveComponent (e.g., a UBoxComponent, USphereComponent, etc.) in the owning actor.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	TObjectPtr<UPrimitiveComponent> CollisionPrimitive;

	/// <summary>
	/// The array of actors that are currently overlapping with the specified collision primitive. This array is updated automatically when actors begin and end overlapping.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	TArray<AActor*> OverlappingActors;

public:
	/// <summary>
	/// Returns the array of actors that are currently overlapping with the specified collision primitive. This function provides a way to access the list of overlapping actors from other parts of the code or Blueprints.
	/// </summary>
	/// <returns>The array of overlapping actors. Can be empty if no actors are overlapping.</returns>
	TArray<AActor*> GetOverlappingActors() const;
};
