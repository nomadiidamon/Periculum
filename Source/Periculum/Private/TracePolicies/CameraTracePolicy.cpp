// Fill out your copyright notice in the Description page of Project Settings.


#include "TracePolicies/CameraTracePolicy.h"

FTracePolicyResult UCameraTracePolicy::Apply_Implementation(UObject* Target) const
{
	FTracePolicyResult Result;
	Result.PolicyTag = PolicyTag;

	AActor* Actor = Cast<AActor>(Target);
	if (!Actor)
	{
		return Result;
	}

	UWorld* World = Actor->GetWorld();
	if (!World)
	{
		return Result;
	}

	if (!CameraComponent.IsValid())
	{
		return Result;
	}

	const FVector CameraLocation = CameraComponent->GetComponentLocation();
	const FRotator CameraRotation = CameraComponent->GetComponentRotation();

	const FVector StartLocation = CameraLocation + CameraRotation.RotateVector(StartOffset);
	const float TraceDistance = EndOffset.Size();
	const FVector EndLocation = StartLocation + CameraRotation.Vector() * TraceDistance;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Actor);

	FCollisionShape Shape;

	switch (CameraTraceType)
	{
	case ECameraTraceType::Cam_LineTrace:
	{
		QueryParams.bTraceComplex = bLineTraceComplex;

		if (bMultiTrace)
		{
			Result.bHit = World->LineTraceMultiByChannel(Result.Hits, StartLocation, EndLocation, TraceChannel, QueryParams);
		}
		else
		{
			FHitResult Hit;
			Result.bHit = World->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, TraceChannel, QueryParams);
			if (Result.bHit)
			{
				Result.Hits.Add(Hit);
			}
		}
		if (bDrawDebug)
		{
			if (Result.bHit)
			{
				DrawDebugLine(World, StartLocation, Result.Hits[0].Location, FColor::Red, false, 1.0f);
				DrawDebugSphere(World, Result.Hits[0].Location, 5.0f, 8, FColor::Red, false, 1.0f);
			}
			else
			{
				DrawDebugLine(World, StartLocation, EndLocation, Result.bHit ? FColor::Red : FColor::Green, false, 1.0f);
				DrawDebugSphere(World, EndLocation, 5.0f, 8, Result.bHit ? FColor::Red : FColor::Green, false, 1.0f);
			}
		}
		break;
	}

	case ECameraTraceType::Cam_SphereTrace:
	{
		Shape = FCollisionShape::MakeSphere(SphereRadius);
		if (bMultiTrace)
		{
			Result.bHit = World->SweepMultiByChannel(Result.Hits, StartLocation, EndLocation, FQuat::Identity, TraceChannel, Shape, QueryParams);
		}
		else
		{
			FHitResult Hit;
			Result.bHit = World->SweepSingleByChannel(Hit, StartLocation, EndLocation, FQuat::Identity, TraceChannel, Shape, QueryParams);
			if (Result.bHit)
			{
				Result.Hits.Add(Hit);
			}
		}
		if (bDrawDebug)
		{
			if (Result.bHit)
			{
				DrawDebugSphere(World, Result.Hits[0].Location, SphereRadius, 16, FColor::Red, false, 1.0f);
			}
			else
			{
				DrawDebugSphere(World, EndLocation, SphereRadius, 16, Result.bHit ? FColor::Red : FColor::Green, false, 1.0f);
			}
		}
		break;
	}

	case ECameraTraceType::Cam_CapsuleTrace:
	{
		Shape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);
		if (bMultiTrace)
		{
			Result.bHit = World->SweepMultiByChannel(Result.Hits, StartLocation, EndLocation, FQuat::Identity, TraceChannel, Shape, QueryParams);
		}
		else
		{
			FHitResult Hit;
			Result.bHit = World->SweepSingleByChannel(Hit, StartLocation, EndLocation, FQuat::Identity, TraceChannel, Shape, QueryParams);
			if (Result.bHit)
			{
				Result.Hits.Add(Hit);
			}
		}
		if (bDrawDebug)
		{
			if (Result.bHit)
			{
				DrawDebugCapsule(World, Result.Hits[0].Location, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, FColor::Red, false, 1.0f);
			}
			else
			{
				DrawDebugCapsule(World, EndLocation, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, Result.bHit ? FColor::Red : FColor::Green, false, 1.0f);
			}
		}
		break;
	}

	case ECameraTraceType::Cam_BoxTrace:
	{
		Shape = FCollisionShape::MakeBox(BoxHalfExtent);
		if (bMultiTrace)
		{
			Result.bHit = World->SweepMultiByChannel(Result.Hits, StartLocation, EndLocation, FQuat::Identity, TraceChannel, Shape, QueryParams);
		}
		else
		{
			FHitResult Hit;
			Result.bHit = World->SweepSingleByChannel(Hit, StartLocation, EndLocation, FQuat::Identity, TraceChannel, Shape, QueryParams);
			if (Result.bHit)
			{
				Result.Hits.Add(Hit);
			}
		}
		if (bDrawDebug)
		{
			FVector BoxHalfSize = FVector(BoxHalfExtent.X, BoxHalfExtent.Y, BoxHalfExtent.Z);
			if (Result.bHit)
			{
				DrawDebugBox(World, Result.Hits[0].Location, BoxHalfSize, FColor::Red, false, 1.0f);
			}
			else
			{
				DrawDebugBox(World, EndLocation, BoxHalfSize, Result.bHit ? FColor::Red : FColor::Green, false, 1.0f);
			}
		}
		break;
	}

	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown CameraTraceType: %d"), static_cast<int32>(CameraTraceType));
		break;
	}

	if (OnTracePolicyCompleted.IsBound())
	{
		OnTracePolicyCompleted.Broadcast(Result);
	}

	return Result;

}
