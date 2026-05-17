#include "Code/Components/CapsuleSpawnerComponent.h"
#include "Components/CapsuleComponent.h"
#include "Code/Utility/CapsuleComponentUtilities.h"
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

	if (SpawnParams.LocationMode == ESpawnLocationMode::InsideShape)
	{
		SpawnData.SpawnTransform.SetLocation(CapsuleComponentUtilities::GetRandomPointInCapsule(CapsuleComponent, RandomStream));
	}
	else if (SpawnParams.LocationMode == ESpawnLocationMode::OnShapeSurface)
	{
		SpawnData.SpawnTransform.SetLocation(CapsuleComponentUtilities::GetRandomPointOnCapsuleSurface(CapsuleComponent, RandomStream));
	}

	if (SpawnParams.RotationMode == ESpawnRotationMode::RandomRotation)
	{
		SpawnData.SpawnTransform.SetRotation(CapsuleComponentUtilities::GetRandomRotation(RandomStream).Quaternion());
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
		SpawnData.SpawnTransform.SetScale3D(CapsuleComponentUtilities::GetRandomUniformScale(SpawnParams, RandomStream));
	}
	else if (SpawnParams.ScaleMode == ESpawnScaleMode::NonUniform)
	{
		SpawnData.SpawnTransform.SetScale3D(CapsuleComponentUtilities::GetRandomNonUniformScale(SpawnParams, RandomStream));
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