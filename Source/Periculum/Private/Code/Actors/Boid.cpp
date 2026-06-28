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

	USphereComponent* OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlappingSphereComponent"));
	OverlapSphere->SetSphereRadius(FlockingComponent->FlockSettings.CollisionDetectionRadius);
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
		if (!FlockingComponent->OverlappingSphereComponent->OnComponentBeginOverlap.IsAlreadyBound(FlockingComponent.Get(), &UFlockingComponent::OnOverlapBegin))
		{
			FlockingComponent->OverlappingSphereComponent->OnComponentBeginOverlap.AddDynamic(FlockingComponent.Get(), &UFlockingComponent::OnOverlapBegin);
		}
		if (!FlockingComponent->OverlappingSphereComponent->OnComponentEndOverlap.IsAlreadyBound(FlockingComponent.Get(), &UFlockingComponent::OnOverlapEnd))
		{
			FlockingComponent->OverlappingSphereComponent->OnComponentEndOverlap.AddDynamic(FlockingComponent.Get(), &UFlockingComponent::OnOverlapEnd);
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


void ABoid::UpdateFlockSettings(const FFlockSettings& NewSettings)
{
	FlockingComponent->FlockSettings.CohesionWeight = NewSettings.CohesionWeight;
	FlockingComponent->FlockSettings.CohesionRadius = NewSettings.CohesionRadius;

	FlockingComponent->FlockSettings.SeparationWeight = NewSettings.SeparationWeight;
	FlockingComponent->FlockSettings.SeparationRadius = NewSettings.SeparationRadius;

	FlockingComponent->FlockSettings.AlignmentWeight = NewSettings.AlignmentWeight;
	FlockingComponent->FlockSettings.AlignmentRadius = NewSettings.AlignmentRadius;

	if (FlockingComponent->OverlappingSphereComponent)
	{
		FlockingComponent->OverlappingSphereComponent->SetSphereRadius(FlockingComponent->FlockSettings.CollisionDetectionRadius);
	}

	FlockingComponent->FlockSettings.MaxSpeed = NewSettings.MaxSpeed;
	FlockingComponent->FlockSettings.MinSpeed = NewSettings.MinSpeed;

	FlockingComponent->FlockSettings.MaxWanderStrength = NewSettings.MaxWanderStrength;
	FlockingComponent->FlockSettings.MinWanderStrength = NewSettings.MinWanderStrength;

	FlockingComponent->FlockSettings.MaxForce = NewSettings.MaxForce;
	FlockingComponent->FlockSettings.TurnSpeed = NewSettings.TurnSpeed;

	FlockingComponent->FlockSettings.FlockCenter = NewSettings.FlockCenter;
	FlockingComponent->FlockSettings.FlockCenterStrength = NewSettings.FlockCenterStrength;

	FlockingComponent->FlockSettings.FlockAttractionPoint = NewSettings.FlockAttractionPoint;
	FlockingComponent->FlockSettings.FlockAttractionPointStrength = NewSettings.FlockAttractionPointStrength;

	FlockingComponent->FlockSettings.bDrawDebugRadiusAverage = NewSettings.bDrawDebugRadiusAverage;
	FlockingComponent->FlockSettings.bDrawDebugSightLine = NewSettings.bDrawDebugSightLine;
}

FVector ABoid::GetFlockingVelocity() const
{
	return FlockingComponent ? FlockingComponent->Velocity : FVector::ZeroVector;
}