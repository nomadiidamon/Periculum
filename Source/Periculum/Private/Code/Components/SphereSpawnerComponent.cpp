#include "Code/Components/SphereSpawnerComponent.h"
#include "Components/SphereComponent.h"
#include "Periculum/Periculum.h"

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
		UE_LOG(GAME, Warning, TEXT("SphereComponent is not assigned in SphereSpawnerComponent. Please assign a SphereComponent to define the spawn area."));
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
		UE_LOG(GAME, Warning, TEXT("Cannot generate spawn data because SphereComponent is not assigned in SphereSpawnerComponent."));
		return FSphereSpawnData();
	}

	FSphereSpawnData SpawnData;

	if (SpawnParams.LocationMode == ESpawnLocationMode::InsideSphere)
	{
		SpawnData.SpawnTransform.SetLocation(GetRandomPointInSphere());
	}
	else if (SpawnParams.LocationMode == ESpawnLocationMode::OnSphereSurface)
	{
		SpawnData.SpawnTransform.SetLocation(GetRandomPointOnSphereSurface());
	}

	if (SpawnParams.RotationMode == ESpawnRotationMode::RandomRotation)
	{
		SpawnData.SpawnTransform.SetRotation(GetRandomRotation().Quaternion());
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
		SpawnData.SpawnTransform.SetScale3D(GetRandomUniformScale());
	}
	else if (SpawnParams.ScaleMode == ESpawnScaleMode::NonUniform)
	{
		SpawnData.SpawnTransform.SetScale3D(GetRandomNonUniformScale());
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

FVector USphereSpawnerComponent::GetRandomPointInSphere() const
{
	float Radius = SphereComponent->GetScaledSphereRadius();
	float ScaledRadius = Radius * FMath::Pow(RandomStream.FRand(), 1.0f / 3.0f);
	FVector localPoint = RandomStream.VRand() * ScaledRadius;
	return SphereComponent->GetComponentTransform().TransformPosition(localPoint);
}

FVector USphereSpawnerComponent::GetRandomPointOnSphereSurface() const
{
	float Radius = SphereComponent->GetScaledSphereRadius();
	FVector localPoint = RandomStream.VRand() * Radius;
	return SphereComponent->GetComponentTransform().TransformPosition(localPoint);
}

FVector USphereSpawnerComponent::GetRandomRadialDirection() const
{
	FVector localDirection = RandomStream.VRand();
	return SphereComponent->GetComponentTransform().TransformVectorNoScale(localDirection).GetSafeNormal();
}

FRotator USphereSpawnerComponent::GetRandomRotation() const
{
	FRotator RandomRotation = FRotator(RandomStream.FRandRange(0.0f, 360.0f), RandomStream.FRandRange(0.0f, 360.0f), RandomStream.FRandRange(0.0f, 360.0f));
	return RandomRotation;
}

FVector USphereSpawnerComponent::GetRandomUniformScale() const
{
	float UniformScale = RandomStream.FRandRange(SpawnParams.MinUniformScale, SpawnParams.MaxUniformScale);
	return FVector(UniformScale);
}

FVector USphereSpawnerComponent::GetRandomNonUniformScale() const
{
	FVector NonUniformScale;
	NonUniformScale.X = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.X, SpawnParams.MaxNonUniformScale.X);
	NonUniformScale.Y = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.Y, SpawnParams.MaxNonUniformScale.Y);
	NonUniformScale.Z = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.Z, SpawnParams.MaxNonUniformScale.Z);
	return NonUniformScale;
}
