#include "Code/Components/BoxSpawnerComponent.h"
#include "Components/BoxComponent.h"
#include "Code/Utility/BoxComponentUtilities.h"
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
	if (SpawnParams.LocationMode == ESpawnLocationMode::InsideShape)
	{
		SpawnData.SpawnTransform.SetLocation(BoxComponentUtilities::GetRandomPointInBox(BoxComponent, RandomStream));
	}
	else if (SpawnParams.LocationMode == ESpawnLocationMode::OnShapeSurface)
	{
		SpawnData.SpawnTransform.SetLocation(BoxComponentUtilities::GetRandomPointOnBoxSurface(BoxComponent, RandomStream));
	}

	// ---------------- ROTATION ----------------
	if (SpawnParams.RotationMode == ESpawnRotationMode::RandomRotation)
	{
		SpawnData.SpawnTransform.SetRotation(BoxComponentUtilities::GetRandomRotation(RandomStream).Quaternion());
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
		SpawnData.SpawnTransform.SetScale3D(BoxComponentUtilities::GetRandomUniformScale(SpawnParams, RandomStream));
	}
	else if (SpawnParams.ScaleMode == ESpawnScaleMode::NonUniform)
	{
		SpawnData.SpawnTransform.SetScale3D(BoxComponentUtilities::GetRandomNonUniformScale(SpawnParams, RandomStream));
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
