#include "Code/Actors/Boid.h"

#include "Code/Components/FlockingComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

#include "Code/Utility/PericulumLog.h"

ABoid::ABoid()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	FlockingComponent = CreateDefaultSubobject<UFlockingComponent>(TEXT("FlockingComponent"));

	USphereComponent* OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlappingComponent"));
	OverlapSphere->SetSphereRadius(FlockingComponent->FlockSettings.SafeRadius);
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapSphere->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OverlapSphere->SetGenerateOverlapEvents(true);

	FlockingComponent->OverlappingComponent = OverlapSphere;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ABoid::BeginPlay()
{
	Super::BeginPlay();

	if (!FlockingComponent)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "FlockingComponent is not set on %s", *GetName());
		return;
	}

	if (!FlockingComponent->OverlappingComponent)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "OverlappingComponent is not set on %s", *GetName());
		return;
	}

	if (FlockingComponent && FlockingComponent->FlockManager)
	{
		FlockingComponent->Velocity = GetActorForwardVector() * FMath::RandRange(FlockingComponent->FlockSettings.MinSpeed, FlockingComponent->FlockSettings.MaxSpeed);
	}

	if (FlockingComponent && FlockingComponent->OverlappingComponent)
	{
		if (!FlockingComponent->OverlappingComponent->OnComponentBeginOverlap.IsAlreadyBound(FlockingComponent, &UFlockingComponent::OnOverlapBegin))
		{
			FlockingComponent->OverlappingComponent->OnComponentBeginOverlap.AddDynamic(FlockingComponent, &UFlockingComponent::OnOverlapBegin);
		}
		if (!FlockingComponent->OverlappingComponent->OnComponentEndOverlap.IsAlreadyBound(FlockingComponent, &UFlockingComponent::OnOverlapEnd))
		{
			FlockingComponent->OverlappingComponent->OnComponentEndOverlap.AddDynamic(FlockingComponent, &UFlockingComponent::OnOverlapEnd);
		}
	}
}

void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FlockingComponent) {
		bDrawDebug = FlockingComponent->FlockSettings.bDrawDebug;
	}

	if (bDrawDebug && FlockingComponent)
	{
		FlockingComponent->DrawOverlapComponentBounds();
	}
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + FlockingComponent->Velocity.GetSafeNormal() * 500.f, FColor::Green, false, -1.f, 0, 2.f);
}
