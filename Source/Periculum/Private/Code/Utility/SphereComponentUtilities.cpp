#include "Code/Utility/SphereComponentUtilities.h"
#include "Components/SphereComponent.h"

FVector SphereComponentUtilities::GetRandomPointInSphere(const USphereComponent* SphereComponent, FRandomStream& RandomStream)
{
	float Radius = SphereComponent->GetScaledSphereRadius();
	float ScaledRadius = Radius * FMath::Pow(RandomStream.FRand(), 1.0f / 3.0f);
	FVector localPoint = RandomStream.VRand() * ScaledRadius;
	return SphereComponent->GetComponentTransform().TransformPosition(localPoint);
}

FVector SphereComponentUtilities::GetRandomPointOnSphereSurface(const USphereComponent* SphereComponent, FRandomStream& RandomStream)
{
	float Radius = SphereComponent->GetScaledSphereRadius();
	FVector localPoint = RandomStream.VRand() * Radius;
	return SphereComponent->GetComponentTransform().TransformPosition(localPoint);
}

FVector SphereComponentUtilities::GetRandomRadialDirection(const USphereComponent* SphereComponent, FRandomStream& RandomStream)
{
	FVector localDirection = RandomStream.VRand();
	return SphereComponent->GetComponentTransform().TransformVectorNoScale(localDirection).GetSafeNormal();
}

FRotator SphereComponentUtilities::GetRandomRotation(FRandomStream& RandomStream)
{
	FRotator RandomRotation = FRotator(RandomStream.FRandRange(0.0f, 360.0f), RandomStream.FRandRange(0.0f, 360.0f), RandomStream.FRandRange(0.0f, 360.0f));
	return RandomRotation;
}

FVector SphereComponentUtilities::GetRandomUniformScale(const FSphereSpawnParams& SpawnParams, FRandomStream& RandomStream)
{
	float UniformScale = RandomStream.FRandRange(SpawnParams.MinUniformScale, SpawnParams.MaxUniformScale);
	return FVector(UniformScale);
}

FVector SphereComponentUtilities::GetRandomNonUniformScale(const FSphereSpawnParams& SpawnParams, FRandomStream& RandomStream)
{
	FVector NonUniformScale;
	NonUniformScale.X = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.X, SpawnParams.MaxNonUniformScale.X);
	NonUniformScale.Y = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.Y, SpawnParams.MaxNonUniformScale.Y);
	NonUniformScale.Z = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.Z, SpawnParams.MaxNonUniformScale.Z);
	return NonUniformScale;
}