#include "Code/Components/CapsuleSpawnerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Code/Utility/PericulumLog.h"

UCapsuleSpawnerComponent::UCapsuleSpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SpawnAreaCapsule"));
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UCapsuleSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	SetRandomSeed(RandomSeed);
}

void UCapsuleSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

void UCapsuleSpawnerComponent::OnRegister()
{
	Super::OnRegister();
	if (!CapsuleComponent)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "CapsuleComponent is not assigned in CapsuleSpawnerComponent. Please assign a CapsuleComponent to define the spawn area.");
	}
	SetRandomSeed(RandomSeed);
}

void UCapsuleSpawnerComponent::DrawDebugSpawnArea() const
{
	DrawDebugCapsule(GetWorld(), CapsuleComponent->GetComponentLocation(), CapsuleComponent->GetScaledCapsuleHalfHeight(), 
		CapsuleComponent->GetScaledCapsuleRadius(), CapsuleComponent->GetComponentQuat(), FColor::Green, false, -1, 0, 2);

	FRotator Rotation = CapsuleComponent->GetComponentRotation();
	Rotation += FRotator(0, 45, 0);

	DrawDebugCapsule(GetWorld(), CapsuleComponent->GetComponentLocation(), CapsuleComponent->GetScaledCapsuleHalfHeight(), 
		CapsuleComponent->GetScaledCapsuleRadius(), Rotation.Quaternion(), FColor::Green, false, -1, 0, 2);

	Rotation += FRotator(0, 45, 0);

	DrawDebugCapsule(GetWorld(), CapsuleComponent->GetComponentLocation(), CapsuleComponent->GetScaledCapsuleHalfHeight(),
		CapsuleComponent->GetScaledCapsuleRadius(), Rotation.Quaternion(), FColor::Green, false, -1, 0, 2);
}

void UCapsuleSpawnerComponent::DrawDebugLastSpawnPoint() const
{
	DrawDebugSphere(GetWorld(), LastSpawnLocation, 10.0f, 15, FColor::Red, false, -1.0f, 0, 2.0f);

}

FCapsuleSpawnData UCapsuleSpawnerComponent::GenerateSpawnData()
{
	if (!ensure(CapsuleComponent))
	{
		PERICULUM_LOG(Periculum_Game, Warning, "Cannot generate spawn data because CapsuleComponent is not assigned in CapsuleSpawnerComponent.");
		return FCapsuleSpawnData();
	}

	FCapsuleSpawnData SpawnData;

	if (SpawnParams.LocationMode == ESpawnLocationMode::InsideCapsule)
	{
		SpawnData.SpawnTransform.SetLocation(GetRandomPointInCapsule());
	}
	else if (SpawnParams.LocationMode == ESpawnLocationMode::OnCapsuleSurface)
	{
		SpawnData.SpawnTransform.SetLocation(GetRandomPointOnCapsuleSurface());
	}

	if (SpawnParams.RotationMode == ESpawnRotationMode::RandomRotation)
	{
		SpawnData.SpawnTransform.SetRotation(GetRandomRotation().Quaternion());
		SpawnData.SpawnDirection = SpawnData.SpawnTransform.GetRotation().GetForwardVector();
	}
	else if (SpawnParams.RotationMode == ESpawnRotationMode::AlignToDirection)
	{
		FVector Center = CapsuleComponent->GetComponentLocation();
		FVector Location = SpawnData.SpawnTransform.GetLocation();
		FVector RadialDirection = (Location - Center).GetSafeNormal();
		if (RadialDirection.IsNearlyZero()) {
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

FCapsuleSpawnData UCapsuleSpawnerComponent::GenerateAndStoreSpawnData()
{
	FCapsuleSpawnData SpawnData = GenerateSpawnData();
	SpawnHistory.Add(SpawnData);
	if (SpawnHistory.Num() > MaxSpawnHistory)
	{
		SpawnHistory.RemoveAt(0);
	}
	return SpawnData;
}

FVector UCapsuleSpawnerComponent::GetRandomPointInCapsule() const
{
	float HalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
	float Radius = CapsuleComponent->GetScaledCapsuleRadius();

	float CylinderHalfHeight = FMath::Max(0.f, HalfHeight - Radius);

	float CylinderVolume = PI * Radius * Radius * (2.f * CylinderHalfHeight);
	float SphereVolume = (4.f / 3.f) * PI * Radius * Radius * Radius;

	float Pick = FMath::FRand() * (CylinderVolume + SphereVolume);

	FVector LocalPoint;

	if (Pick < CylinderVolume)
	{
		// ---------------- CYLINDER ----------------
		float Z = FMath::FRandRange(-CylinderHalfHeight, CylinderHalfHeight);

		float Angle = FMath::FRandRange(0.f, 2.f * PI);
		float R = Radius * FMath::Sqrt(FMath::FRand());

		LocalPoint = FVector(
			R * FMath::Cos(Angle),
			R * FMath::Sin(Angle),
			Z
		);
	}
	else
	{
		// ------------- CAPS (2 hemispheres) -------------

		float Z = FMath::FRandRange(-1.f, 1.f);
		float Theta = FMath::FRandRange(0.f, 2.f * PI);
		float R = FMath::Sqrt(1.f - Z * Z);

		FVector Dir(
			R * FMath::Cos(Theta),
			R * FMath::Sin(Theta),
			Z
		);

		float Sign = (FMath::FRand() < 0.5f) ? 1.f : -1.f;

		LocalPoint = FVector(
			Dir.X * Radius,
			Dir.Y * Radius,
			Sign * CylinderHalfHeight + Dir.Z * Radius
		);
	}

	return CapsuleComponent->GetComponentTransform().TransformPosition(LocalPoint);
}

FVector UCapsuleSpawnerComponent::GetRandomPointOnCapsuleSurface() const
{
	float HalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
	float Radius = CapsuleComponent->GetScaledCapsuleRadius();

	float CylinderHalfHeight = FMath::Max(0.f, HalfHeight - Radius);

	float CylinderArea = 2.f * PI * Radius * (2.f * CylinderHalfHeight);
	float SphereArea = 4.f * PI * Radius * Radius;

	float Pick = FMath::FRand() * (CylinderArea + SphereArea);

	FVector LocalPoint;

	if (Pick < CylinderArea)
	{
		// ---------------- CYLINDER SIDE ----------------
		float Angle = FMath::FRandRange(0.f, 2.f * PI);
		float Z = FMath::FRandRange(-CylinderHalfHeight, CylinderHalfHeight);

		LocalPoint = FVector(
			Radius * FMath::Cos(Angle),
			Radius * FMath::Sin(Angle),
			Z
		);
	}
	else
	{
		// ---------------- SPHERICAL CAPS ----------------

		float Z = FMath::FRandRange(-1.f, 1.f);
		float Theta = FMath::FRandRange(0.f, 2.f * PI);
		float R = FMath::Sqrt(1.f - Z * Z);

		FVector Dir(
			R * FMath::Cos(Theta),
			R * FMath::Sin(Theta),
			Z
		);

		float Sign = (FMath::FRand() < 0.5f) ? 1.f : -1.f;

		LocalPoint = FVector(
			Dir.X * Radius,
			Dir.Y * Radius,
			Sign * CylinderHalfHeight + Dir.Z * Radius
		);
	}

	return CapsuleComponent->GetComponentTransform().TransformPosition(LocalPoint);
}

FVector UCapsuleSpawnerComponent::GetRandomRadialDirection() const
{
	FVector LocalDirection = FMath::VRand();
	return CapsuleComponent->GetComponentTransform().TransformVectorNoScale(LocalDirection).GetSafeNormal();
}

FRotator UCapsuleSpawnerComponent::GetRandomRotation() const
{
	FRotator RandomRotation = FRotator(FMath::FRandRange(0.0f, 360.0f), FMath::FRandRange(0.0f, 360.0f), FMath::FRandRange(0.0f, 360.0f));
	return RandomRotation;
}

FVector UCapsuleSpawnerComponent::GetRandomUniformScale() const
{
	float UniformScale = FMath::FRandRange(SpawnParams.MinUniformScale, SpawnParams.MaxUniformScale);
	return FVector(UniformScale);
}

FVector UCapsuleSpawnerComponent::GetRandomNonUniformScale() const
{
	FVector NonUniformScale;
	NonUniformScale.X = FMath::FRandRange(SpawnParams.MinNonUniformScale.X, SpawnParams.MaxNonUniformScale.X);
	NonUniformScale.Y = FMath::FRandRange(SpawnParams.MinNonUniformScale.Y, SpawnParams.MaxNonUniformScale.Y);
	NonUniformScale.Z = FMath::FRandRange(SpawnParams.MinNonUniformScale.Z, SpawnParams.MaxNonUniformScale.Z);
	return NonUniformScale;
}