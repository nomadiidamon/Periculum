#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ModularActor.generated.h"

UCLASS()
class PERICULUM_API AModularActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AModularActor();

	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

};
