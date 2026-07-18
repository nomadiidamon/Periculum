#include "Actors/Boid.h"
#include "Actors/BoidFlock.h"

#include "ActorComponents/FlockingComponent.h"
#include "ActorComponents/TraceComponent.h"
#include "ActorComponents/MessagingComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "TracePolicies/SphereTracePolicy.h"

#include "DataAssets/BoidFlockSettings.h"

#include "Defines/PericulumLog.h"

ABoid::ABoid()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	FlockingComponent = CreateDefaultSubobject<UFlockingComponent>(TEXT("FlockingComponent"));

	USphereComponent* OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlappingSphereComponent"));
	OverlapSphere->SetSphereRadius(FlockingComponent->BoidSettings.AlignmentRadius);
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapSphere->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OverlapSphere->SetGenerateOverlapEvents(true);

	FlockingComponent->OverlappingSphereComponent = OverlapSphere;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	TraceComponent = CreateDefaultSubobject<UTraceComponent>(TEXT("TraceComponent"));

	MessagingComponent = CreateDefaultSubobject<UMessagingComponent>(TEXT("MessagingComponent"));
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
		float minSpeed = FlockingComponent->FlockManager->FlockSettings->MinSpeed;
		float maxSpeed = FlockingComponent->FlockManager->FlockSettings->MaxSpeed;
		FlockingComponent->BoidSettings.Velocity = GetActorForwardVector() * FMath::RandRange(minSpeed, maxSpeed);
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

	if (TraceComponent) {

		{ // Create a SphereTracePolicy for obstacle detection
			USphereTracePolicy* ObstacleTracePolicy = NewObject<USphereTracePolicy>(this, USphereTracePolicy::StaticClass());
			ObstacleTracePolicy->StartOffset = FVector::ZeroVector;
			ObstacleTracePolicy->EndOffset = FVector(500.0f, 0.0f, 0.0f);
			ObstacleTracePolicy->Radius = 100.0f;
			ObstacleTracePolicy->TraceChannel = ECollisionChannel::ECC_WorldDynamic;
			ObstacleTracePolicy->bMultiTrace = true;
			ObstacleTracePolicy->bDrawDebug = false;
			ObstacleTracePolicy->OnTracePolicyCompleted.AddDynamic(this, &ABoid::HandleObstacleDetection);
			TraceComponent->AddRuntimePolicy(ObstacleTracePolicy);
		}
	}
}

void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoid::HandleObstacleDetection(FTracePolicyResult Result)
{
	if (Result.bHit)
	{
		for (const FHitResult& Hit : Result.Hits)
		{
			if (FlockingComponent)
			{
				FlockingComponent->AvoidObstacle(Hit.ImpactPoint, Hit.ImpactNormal, FlockingComponent->BoidSettings.Velocity);
			}
			else {
				PERICULUM_LOG(Periculum_Game, Warning, "FlockingComponent is not set on %s", *GetName());
			}
		}
	}
}
