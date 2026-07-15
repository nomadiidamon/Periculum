#include "ActorComponents/OverlappingComponent.h"
#include "Defines/PericulumLog.h"

UOverlappingComponent::UOverlappingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CollisionPrimitive = nullptr;
}

void UOverlappingComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UOverlappingComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is valid and not the owner of this component
	if (OtherActor && OtherActor != GetOwner())
	{
		// Add the overlapping actor to the array
		OverlappingActors.AddUnique(OtherActor);
		PERICULUM_LOG(Periculum_Game, Log, "Actor %s has begun overlapping with %s", *OtherActor->GetName(), *GetOwner()->GetName());
	}
}

void UOverlappingComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the overlapping actor is valid and not the owner of this component
	if (OtherActor && OtherActor != GetOwner())
	{
		// Remove the overlapping actor from the array
		OverlappingActors.Remove(OtherActor);
		PERICULUM_LOG(Periculum_Game, Log, "Actor %s has ended overlapping with %s", *OtherActor->GetName(), *GetOwner()->GetName());
	}
}

TArray<AActor*> UOverlappingComponent::GetOverlappingActors() const
{
	if (OverlappingActors.Num() == 0)
	{
		//PERICULUM_LOG(Periculum_Game, Log, "No actors are currently overlapping with %s", *GetOwner()->GetName());
		return TArray<AActor*>();
	}

	TArray<AActor*> ValidOverlappingActors;
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->IsValidLowLevel())
		{
			ValidOverlappingActors.Add(Actor);
		}
		else
		{
			//PERICULUM_LOG(Periculum_Game, Warning, "Invalid actor found in OverlappingActors array of %s. Removing it.", *GetOwner()->GetName());
			const_cast<TArray<AActor*>&>(OverlappingActors).Remove(Actor);
		}
	}

	if (ValidOverlappingActors.Num() == 0)
	{
		//PERICULUM_LOG(Periculum_Game, Log, "All actors in OverlappingActors array of %s are invalid. Returning an empty array.", *GetOwner()->GetName());
	}
	else {
		PERICULUM_LOG(Periculum_Game, Log, "%d valid actors are currently overlapping with %s", ValidOverlappingActors.Num(), *GetOwner()->GetName());
	}

	return ValidOverlappingActors;
}

