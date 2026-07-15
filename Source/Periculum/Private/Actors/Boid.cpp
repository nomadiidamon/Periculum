#include "Actors/Boid.h"

#include "ActorComponents/FlockingComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

#include "Defines/PericulumLog.h"

ABoid::ABoid()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	FlockingComponent = CreateDefaultSubobject<UFlockingComponent>(TEXT("FlockingComponent"));

	USphereComponent* OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlappingSphereComponent"));
	OverlapSphere->SetSphereRadius(FlockingComponent->FlockSettings.AlignmentRadius);
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapSphere->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OverlapSphere->SetGenerateOverlapEvents(true);

	FlockingComponent->OverlappingSphereComponent = OverlapSphere;

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

	if (!FlockingComponent->OverlappingSphereComponent)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "OverlappingSphereComponent is not set on %s", *GetName());
		return;
	}

	if (FlockingComponent && FlockingComponent->FlockManager)
	{
		FlockingComponent->Velocity = GetActorForwardVector() * FMath::RandRange(FlockingComponent->FlockSettings.MinSpeed, FlockingComponent->FlockSettings.MaxSpeed);
	}

	if (FlockingComponent && FlockingComponent->OverlappingSphereComponent)
	{
		if (!FlockingComponent->OverlappingSphereComponent->OnComponentBeginOverlap.IsAlreadyBound(FlockingComponent, &UFlockingComponent::OnOverlapBegin))
		{
			FlockingComponent->OverlappingSphereComponent->OnComponentBeginOverlap.AddDynamic(FlockingComponent, &UFlockingComponent::OnOverlapBegin);
		}
		if (!FlockingComponent->OverlappingSphereComponent->OnComponentEndOverlap.IsAlreadyBound(FlockingComponent, &UFlockingComponent::OnOverlapEnd))
		{
			FlockingComponent->OverlappingSphereComponent->OnComponentEndOverlap.AddDynamic(FlockingComponent, &UFlockingComponent::OnOverlapEnd);
		}
	}
}

void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FlockingComponent) {

		bDrawDebugRadius = FlockingComponent->FlockSettings.bDrawDebugRadiusAverage;
		bDrawDebugSightLine = FlockingComponent->FlockSettings.bDrawDebugSightLine;

		if (bDrawDebugRadius)
		{
			FlockingComponent->DrawOverlapComponentBounds();
		}
		if (bDrawDebugSightLine)
		{
			DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + FlockingComponent->Velocity.GetSafeNormal() * 500.f, FColor::Green, false, -1.f, 0, 2.f);
		}
	}
}
