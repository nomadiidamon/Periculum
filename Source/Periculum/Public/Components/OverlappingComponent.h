// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OverlappingComponent.generated.h"

class UPrimitiveComponent;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	TObjectPtr<UPrimitiveComponent> CollisionPrimitive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	TArray<AActor*> OverlappingActors;

public:

	TArray<AActor*> GetOverlappingActors() const;
};
