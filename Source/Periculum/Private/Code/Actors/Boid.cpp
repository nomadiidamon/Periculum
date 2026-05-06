#include "Code/Actors/Boid.h"
#include "Code/Components/FlockingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

#include "Periculum/Periculum.h"

ABoid::ABoid()
{
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(50.0f);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionSphere->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	FlockingComponent = CreateDefaultSubobject<UFlockingComponent>(TEXT("FlockingComponent"));
	FlockingComponent->OverlappingComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(FlockingComponent->safeRadius);
}

void ABoid::BeginPlay()
{
	Super::BeginPlay();
	
	if (!FlockingComponent)
	{
		UE_LOG(GAME, Warning, TEXT("FlockingComponent is not set on %s"), *GetName());
	}

	if (FlockingComponent && FlockingComponent->FlockManager)
	{
		FlockingComponent->Velocity = GetActorForwardVector() * FMath::RandRange(FlockingComponent->MinSpeed, FlockingComponent->MaxSpeed);
	}
}

void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + FlockingComponent->Velocity.GetSafeNormal() * 500.f, FColor::Green, false, -1.f, 0, 2.f);
}

