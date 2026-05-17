#include "Code/Components/SphereSpawnerComponent.h"
#include "Components/SphereComponent.h"
#include "Code/Utility/SphereComponentUtilities.h"
#include "Code/Utility/PericulumLog.h"

USphereSpawnerComponent::USphereSpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnAreaSphere"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void USphereSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	SetRandomSeed(RandomSeed);
}

void USphereSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bDebugDrawArea)
	{
		DrawDebugSpawnArea();

		if (bDebugDrawLastPoint)
		{
			DrawDebugLastSpawnPoint();
		}
	}
}

void USphereSpawnerComponent::OnRegister()
{
	Super::OnRegister();
	if (!SphereComponent)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "SphereComponent is not assigned in SphereSpawnerComponent. Please assign a SphereComponent to define the spawn area.");
	}
	SetRandomSeed(RandomSeed);
}

void USphereSpawnerComponent::DrawDebugSpawnArea() const
{
	DrawDebugSphere(GetWorld(), SphereComponent->GetComponentLocation(), SphereComponent->GetScaledSphereRadius(),
		15, FColor::Green, false, -1.0f, 0, 2.0f);
}

void USphereSpawnerComponent::DrawDebugLastSpawnPoint() const
{
	DrawDebugSphere(GetWorld(), LastSpawnLocation, 10.0f, 15, FColor::Red, false, -1.0f, 0, 2.0f);
}

FSphereSpawnData USphereSpawnerComponent::GenerateSpawnData()
{
	if (!ensure(SphereComponent))
	{
		PERICULUM_LOG(Periculum_Game, Warning, "Cannot generate spawn data because SphereComponent is not assigned in SphereSpawnerComponent.");
		return FSphereSpawnData();
	}

	FSphereSpawnData SpawnData;

	if (SpawnParams.LocationMode == ESpawnLocationMode::InsideShape)
	{
		SpawnData.SpawnTransform.SetLocation(SphereComponentUtilities::GetRandomPointInSphere(SphereComponent, RandomStream));
	}
	else if (SpawnParams.LocationMode == ESpawnLocationMode::OnShapeSurface)
	{
		SpawnData.SpawnTransform.SetLocation(SphereComponentUtilities::GetRandomPointOnSphereSurface(SphereComponent, RandomStream));
	}

	if (SpawnParams.RotationMode == ESpawnRotationMode::RandomRotation)
	{
		SpawnData.SpawnTransform.SetRotation(SphereComponentUtilities::GetRandomRotation(RandomStream).Quaternion());
		SpawnData.SpawnDirection = SpawnData.SpawnTransform.GetRotation().GetForwardVector();
	}
	else if (SpawnParams.RotationMode == ESpawnRotationMode::AlignToDirection)
	{
		FVector Center = SphereComponent->GetComponentLocation();
		FVector Location = SpawnData.SpawnTransform.GetLocation();
		FVector RadialDirection = (Location - Center).GetSafeNormal();
		if (RadialDirection.IsNearlyZero())
		{
			RadialDirection = FVector::ForwardVector;
		}
		SpawnData.SpawnDirection = RadialDirection;
		SpawnData.SpawnTransform.SetRotation(RadialDirection.ToOrientationRotator().Quaternion());
	}

	if (SpawnParams.ScaleMode == ESpawnScaleMode::Uniform)
	{
		SpawnData.SpawnTransform.SetScale3D(SphereComponentUtilities::GetRandomUniformScale(SpawnParams, RandomStream));
	}
	else if (SpawnParams.ScaleMode == ESpawnScaleMode::NonUniform)
	{
		SpawnData.SpawnTransform.SetScale3D(SphereComponentUtilities::GetRandomNonUniformScale(SpawnParams, RandomStream));
	}

	LastSpawnLocation = SpawnData.SpawnTransform.GetLocation();

	return SpawnData;
}

FSphereSpawnData USphereSpawnerComponent::GenerateAndStoreSpawnData()
{
	FSphereSpawnData SpawnData = GenerateSpawnData();
	SpawnHistory.Add(SpawnData);
	if (SpawnHistory.Num() > MaxSpawnHistory)
	{
		SpawnHistory.RemoveAt(0);
	}
	return SpawnData;
}