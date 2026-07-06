#include "Utility/BoxComponentUtilities.h"
#include "Components/BoxComponent.h"

FVector BoxComponentUtilities::GetRandomPointInBox(const UBoxComponent* BoxComponent, FRandomStream& RandomStream)
{
	FVector Extent = BoxComponent->GetScaledBoxExtent();

	FVector LocalPoint;
	LocalPoint.X = RandomStream.FRandRange(-Extent.X, Extent.X);
	LocalPoint.Y = RandomStream.FRandRange(-Extent.Y, Extent.Y);
	LocalPoint.Z = RandomStream.FRandRange(-Extent.Z, Extent.Z);

	return BoxComponent->GetComponentTransform().TransformPosition(LocalPoint);
}

FVector BoxComponentUtilities::GetRandomPointOnBoxSurface(const UBoxComponent* BoxComponent, FRandomStream& RandomStream)
{
	FVector Extent = BoxComponent->GetScaledBoxExtent();

	float XY = Extent.X * Extent.Y;
	float XZ = Extent.X * Extent.Z;
	float YZ = Extent.Y * Extent.Z;

	float TotalArea = 2.f * (XY + XZ + YZ);
	float Pick = RandomStream.FRand() * TotalArea;

	FVector LocalPoint;

	// ---------------- ±Z faces ----------------
	if (Pick < XY * 2.f)
	{
		float X = RandomStream.FRandRange(-Extent.X, Extent.X);
		float Y = RandomStream.FRandRange(-Extent.Y, Extent.Y);

		float Sign = (Pick < XY) ? 1.f : -1.f;

		LocalPoint = FVector(X, Y, Sign * Extent.Z);
	}
	// ---------------- ±Y faces ----------------
	else if (Pick < XY * 2.f + XZ * 2.f)
	{
		float X = RandomStream.FRandRange(-Extent.X, Extent.X);
		float Z = RandomStream.FRandRange(-Extent.Z, Extent.Z);

		float Sign = ((Pick - XY * 2.f) < XZ) ? 1.f : -1.f;

		LocalPoint = FVector(X, Sign * Extent.Y, Z);
	}
	// ---------------- ±X faces ----------------
	else
	{
		float Y = RandomStream.FRandRange(-Extent.Y, Extent.Y);
		float Z = RandomStream.FRandRange(-Extent.Z, Extent.Z);

		float Sign = ((Pick - (XY * 2.f + XZ * 2.f)) < YZ) ? 1.f : -1.f;

		LocalPoint = FVector(Sign * Extent.X, Y, Z);
	}

	return BoxComponent->GetComponentTransform().TransformPosition(LocalPoint);
}

FVector BoxComponentUtilities::GetRandomRadialDirection(const UBoxComponent* BoxComponent, FRandomStream& RandomStream)
{
	FVector Center = BoxComponent->GetComponentLocation();
	FVector Point = BoxComponentUtilities::GetRandomPointOnBoxSurface(BoxComponent, RandomStream);

	return (Point - Center).GetSafeNormal();
}

FRotator BoxComponentUtilities::GetRandomRotation(FRandomStream& RandomStream)
{
	return FRotator(
		RandomStream.FRandRange(0.f, 360.f),
		RandomStream.FRandRange(0.f, 360.f),
		RandomStream.FRandRange(0.f, 360.f)
	);
}

FVector BoxComponentUtilities::GetRandomUniformScale(const FBoxSpawnParams& SpawnParams, FRandomStream& RandomStream)
{
	float S = RandomStream.FRandRange(SpawnParams.MinUniformScale, SpawnParams.MaxUniformScale);
	return FVector(S);
}

FVector BoxComponentUtilities::GetRandomNonUniformScale(const FBoxSpawnParams& SpawnParams, FRandomStream& RandomStream)
{
	float X = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.X, SpawnParams.MaxNonUniformScale.X);
	float Y = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.Y, SpawnParams.MaxNonUniformScale.Y);
	float Z = RandomStream.FRandRange(SpawnParams.MinNonUniformScale.Z, SpawnParams.MaxNonUniformScale.Z);
	return FVector(X, Y, Z);
}

