#include "Code/Components/OverlappingComponent.h"

UOverlappingComponent::UOverlappingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CollisionPrimitive = CreateDefaultSubobject<UPrimitiveComponent>(TEXT("CollisionPrimitive"));
}

void UOverlappingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionPrimitive)
	{
		CollisionPrimitive->OnComponentBeginOverlap.AddDynamic(this, &UOverlappingComponent::OnOverlapBegin);
		CollisionPrimitive->OnComponentEndOverlap.AddDynamic(this, &UOverlappingComponent::OnOverlapEnd);
	}
}

void UOverlappingComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is valid and not the owner of this component
	if (OtherActor && OtherActor != GetOwner())
	{
		// Add the overlapping actor to the array
		OverlappingActors.AddUnique(OtherActor);
	}
}

void UOverlappingComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the overlapping actor is valid and not the owner of this component
	if (OtherActor && OtherActor != GetOwner())
	{
		// Remove the overlapping actor from the array
		OverlappingActors.Remove(OtherActor);
	}
}

