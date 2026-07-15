#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ModularActor.generated.h"

/**
 * A modular actor that can be extended with components and functionality.
 */

UCLASS()
class PERICULUM_API AModularActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AModularActor();

	/// <summary>
	/// Lifecycle hook invoked before component initialization. Overrides the base-class implementation to perform any necessary pre-initialization tasks.
	/// Used to register this actor with the UGameFrameworkComponentManager to receive modular components and functionality before it fully initializes.
	/// </summary>
	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

};
