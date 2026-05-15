#include "Code/Components/BoxSpawnerComponent.h"
#include "Components/BoxComponent.h"
#include "Code/Utility/PericulumLog.h"

UBoxSpawnerComponent::UBoxSpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnAreaBox"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UBoxSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	SetRandomSeed(RandomSeed);	
}

void UBoxSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

void UBoxSpawnerComponent::OnRegister()
{
	Super::OnRegister();
	if (!BoxComponent)
	{
		PERICULUM_LOG(Periculum_Game, Warning, "BoxComponent is not assigned in BoxSpawnerComponent. Please assign a BoxComponent to define the spawn area.");
	}
	SetRandomSeed(RandomSeed);
}

void UBoxSpawnerComponent::DrawDebugSpawnArea() const
{
	DrawDebugBox(GetWorld(), BoxComponent->GetComponentLocation(), BoxComponent->GetScaledBoxExtent(),
		BoxComponent->GetComponentRotation().Quaternion(), FColor::Green, false, -1.0f, 0, 2.0f);
}

void UBoxSpawnerComponent::DrawDebugLastSpawnPoint() const
{
	DrawDebugSphere(GetWorld(), LastSpawnLocation, 10.0f, 15, FColor::Red, false, -1.0f, 0, 2.0f);
}

FBoxSpawnData UBoxSpawnerComponent::GenerateSpawnData()
{
	if (!ensure(BoxComponent))
	{
		PERICULUM_LOG(Periculum_Game, Warning, "BoxComponent is not assigned in BoxSpawnerComponent.");
		return FBoxSpawnData();
	}

	FBoxSpawnData SpawnData;

	// ---------------- LOCATION ----------------
	if (SpawnParams.LocationMode == ESpawnLocationMode::InsideBox)
	{
		SpawnData.SpawnTransform.SetLocation(GetRandomPointInBox());
	}
	else if (SpawnParams.LocationMode == ESpawnLocationMode::OnBoxSurface)
	{
		SpawnData.SpawnTransform.SetLocation(GetRandomPointOnBoxSurface());
	}

	// ---------------- ROTATION ----------------
	if (SpawnParams.RotationMode == ESpawnRotationMode::RandomRotation)
	{
		SpawnData.SpawnTransform.SetRotation(GetRandomRotation().Quaternion());
		SpawnData.SpawnDirection = SpawnData.SpawnTransform.GetRotation().GetForwardVector();
	}
	else if (SpawnParams.RotationMode == ESpawnRotationMode::AlignToDirection)
	{
		FVector Center = BoxComponent->GetComponentLocation();
		FVector Location = SpawnData.SpawnTransform.GetLocation();

		FVector Dir = (Location - Center).GetSafeNormal();
		if (Dir.IsNearlyZero())
		{
			Dir = FVector::ForwardVector;
		}

		SpawnData.SpawnDirection = Dir;
		SpawnData.SpawnTransform.SetRotation(Dir.ToOrientationRotator().Quaternion());
	}

	// ---------------- SCALE ----------------
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

FBoxSpawnData UBoxSpawnerComponent::GenerateAndStoreSpawnData()
{
	FBoxSpawnData SpawnData = GenerateSpawnData();

	SpawnHistory.Add(SpawnData);

	if (SpawnHistory.Num() > MaxSpawnHistory)
	{
		SpawnHistory.RemoveAt(0);
	}

	return SpawnData;
}

FVector UBoxSpawnerComponent::GetRandomPointInBox() const
{
	FVector Extent = BoxComponent->GetScaledBoxExtent();

	FVector LocalPoint;
	LocalPoint.X = FMath::FRandRange(-Extent.X, Extent.X);
	LocalPoint.Y = FMath::FRandRange(-Extent.Y, Extent.Y);
	LocalPoint.Z = FMath::FRandRange(-Extent.Z, Extent.Z);

	return BoxComponent->GetComponentTransform().TransformPosition(LocalPoint);
}

FVector UBoxSpawnerComponent::GetRandomPointOnBoxSurface() const
{
	FVector Extent = BoxComponent->GetScaledBoxExtent();

	float XY = Extent.X * Extent.Y;
	float XZ = Extent.X * Extent.Z;
	float YZ = Extent.Y * Extent.Z;

	float TotalArea = 2.f * (XY + XZ + YZ);
	float Pick = FMath::FRand() * TotalArea;

	FVector LocalPoint;

	// ---------------- ±Z faces ----------------
	if (Pick < XY * 2.f)
	{
		float X = FMath::FRandRange(-Extent.X, Extent.X);
		float Y = FMath::FRandRange(-Extent.Y, Extent.Y);

		float Sign = (Pick < XY) ? 1.f : -1.f;

		LocalPoint = FVector(X, Y, Sign * Extent.Z);
	}
	// ---------------- ±Y faces ----------------
	else if (Pick < XY * 2.f + XZ * 2.f)
	{
		float X = FMath::FRandRange(-Extent.X, Extent.X);
		float Z = FMath::FRandRange(-Extent.Z, Extent.Z);

		float Sign = ((Pick - XY * 2.f) < XZ) ? 1.f : -1.f;

		LocalPoint = FVector(X, Sign * Extent.Y, Z);
	}
	// ---------------- ±X faces ----------------
	else
	{
		float Y = FMath::FRandRange(-Extent.Y, Extent.Y);
		float Z = FMath::FRandRange(-Extent.Z, Extent.Z);

		float Sign = ((Pick - (XY * 2.f + XZ * 2.f)) < YZ) ? 1.f : -1.f;

		LocalPoint = FVector(Sign * Extent.X, Y, Z);
	}

	return BoxComponent->GetComponentTransform().TransformPosition(LocalPoint);
}

FVector UBoxSpawnerComponent::GetRandomRadialDirection() const
{
	FVector Center = BoxComponent->GetComponentLocation();
	FVector Point = GetRandomPointOnBoxSurface();

	return (Point - Center).GetSafeNormal();
}

FRotator UBoxSpawnerComponent::GetRandomRotation() const
{
	return FRotator(
		FMath::FRandRange(0.f, 360.f),
		FMath::FRandRange(0.f, 360.f),
		FMath::FRandRange(0.f, 360.f)
	);
}

FVector UBoxSpawnerComponent::GetRandomUniformScale() const
{
	float S = FMath::FRandRange(SpawnParams.MinUniformScale, SpawnParams.MaxUniformScale);
	return FVector(S);
}

FVector UBoxSpawnerComponent::GetRandomNonUniformScale() const
{
	float X = FMath::FRandRange(SpawnParams.MinNonUniformScale.X, SpawnParams.MaxNonUniformScale.X);
	float Y = FMath::FRandRange(SpawnParams.MinNonUniformScale.Y, SpawnParams.MaxNonUniformScale.Y);
	float Z = FMath::FRandRange(SpawnParams.MinNonUniformScale.Z, SpawnParams.MaxNonUniformScale.Z);
	return FVector(X, Y, Z);
}