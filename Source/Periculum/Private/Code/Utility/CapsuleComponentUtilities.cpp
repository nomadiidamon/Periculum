#include "Code/Utility/CapsuleComponentUtilities.h"
#include "Components/CapsuleComponent.h"

FVector CapsuleComponentUtilities::GetRandomPointInCapsule(const UCapsuleComponent* CapsuleComponent, FRandomStream& RandomStream)
{
	float HalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
	float Radius = CapsuleComponent->GetScaledCapsuleRadius();

	float CylinderHalfHeight = FMath::Max(0.f, HalfHeight - Radius);

	float CylinderVolume = PI * Radius * Radius * (2.f * CylinderHalfHeight);
	float SphereVolume = (4.f / 3.f) * PI * Radius * Radius * Radius;

	float Pick = RandomStream.FRand() * (CylinderVolume + SphereVolume);

	FVector LocalPoint;

	if (Pick < CylinderVolume)
	{
		// ---------------- CYLINDER ----------------
		float Z = RandomStream.FRandRange(-CylinderHalfHeight, CylinderHalfHeight);

		float Angle = RandomStream.FRandRange(0.f, 2.f * PI);
		float R = Radius * FMath::Sqrt(RandomStream.FRand());

		LocalPoint = FVector(
			R * FMath::Cos(Angle),
			R * FMath::Sin(Angle),
			Z
		);
	}
	else
	{
		// ------------- CAPS (2 hemispheres) -------------

		float Z = RandomStream.FRandRange(-1.f, 1.f);
		float Theta = RandomStream.FRandRange(0.f, 2.f * PI);
		float R = FMath::Sqrt(1.f - Z * Z);

		FVector Dir(
			R * FMath::Cos(Theta),
			R * FMath::Sin(Theta),
			Z
		);

		float Sign = (RandomStream.FRand() < 0.5f) ? 1.f : -1.f;

		LocalPoint = FVector(
			Dir.X * Radius,
			Dir.Y * Radius,
			Sign * CylinderHalfHeight + Dir.Z * Radius
		);
	}

	return CapsuleComponent->GetComponentTransform().TransformPosition(LocalPoint);
}

FVector CapsuleComponentUtilities::GetRandomPointOnCapsuleSurface(const UCapsuleComponent* CapsuleComponent, FRandomStream& RandomStream)
{
	float HalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
	float Radius = CapsuleComponent->GetScaledCapsuleRadius();

	float CylinderHalfHeight = FMath::Max(0.f, HalfHeight - Radius);

	float CylinderArea = 2.f * PI * Radius * (2.f * CylinderHalfHeight);
	float SphereArea = 4.f * PI * Radius * Radius;

	float Pick = RandomStream.FRand() * (CylinderArea + SphereArea);

	FVector LocalPoint;

	if (Pick < CylinderArea)
	{
		// ---------------- CYLINDER SIDE ----------------
		float Angle = RandomStream.FRandRange(0.f, 2.f * PI);
		float Z = RandomStream.FRandRange(-CylinderHalfHeight, CylinderHalfHeight);

		LocalPoint = FVector(
			Radius * FMath::Cos(Angle),
			Radius * FMath::Sin(Angle),
			Z
		);
	}
	else
	{
		// ---------------- SPHERICAL CAPS ----------------

		float Z = RandomStream.FRandRange(-1.f, 1.f);
		float Theta = RandomStream.FRandRange(0.f, 2.f * PI);
		float R = FMath::Sqrt(1.f - Z * Z);

		FVector Dir(
			R * FMath::Cos(Theta),
			R * FMath::Sin(Theta),
			Z
		);

		float Sign = (RandomStream.FRand() < 0.5f) ? 1.f : -1.f;

		LocalPoint = FVector(
			Dir.X * Radius,
			Dir.Y * Radius,
			Sign * CylinderHalfHeight + Dir.Z * Radius
		);
	}

	return CapsuleComponent->GetComponentTransform().TransformPosition(LocalPoint);
}

FVector CapsuleComponentUtilities::GetRandomRadialDirection(const UCapsuleComponent* CapsuleComponent, FRandomStream& RandomStream)
{
	FVector LocalDirection = RandomStream.VRand();
	return CapsuleComponent->GetComponentTransform().TransformVectorNoScale(LocalDirection).GetSafeNormal();
}

FRotator CapsuleComponentUtilities::GetRandomRotation(FRandomStream& RandomStream)
{
	FRotator RandomRotation = FRotator(RandomStream.FRandRange(0.0f, 360.0f), RandomStream.FRandRange(0.0f, 360.0f), RandomStream.FRandRange(0.0f, 360.0f));
	return RandomRotation;
}

FVector CapsuleComponentUtilities::GetRandomUniformScale(const FCapsuleSpawnParams& SpawnParams, FRandomStream& RandomStream)
{
	float UniformScale = RandomStream.FRandRange(SpawnParams.MinUniformScale, SpawnParams.MaxUniformScale);
	return FVector(UniformScale);
}

FVector CapsuleComponentUtilities::GetRandomNonUniformScale(const FCapsuleSpawnParams& SpawnParams, FRandomStream& RandomStream)
{
	FVector NonUniformScale;
	NonUniformScale.X = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.X, SpawnParams.MaxNonUniformScale.X);
	NonUniformScale.Y = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.Y, SpawnParams.MaxNonUniformScale.Y);
	NonUniformScale.Z = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.Z, SpawnParams.MaxNonUniformScale.Z);
	return NonUniformScale;
}
