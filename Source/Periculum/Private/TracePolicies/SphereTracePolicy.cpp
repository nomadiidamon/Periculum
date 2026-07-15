// Fill out your copyright notice in the Description page of Project Settings.


#include "TracePolicies/SphereTracePolicy.h"

FTracePolicyResult USphereTracePolicy::Apply_Implementation(UObject* Target) const
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

	const FVector Start = Actor->GetActorLocation() + Actor->GetActorRotation().RotateVector(StartOffset);
	const FVector End = Actor->GetActorLocation() + Actor->GetActorRotation().RotateVector(EndOffset);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Actor);

	const FCollisionShape Shape = FCollisionShape::MakeSphere(Radius);

	if (bMultiTrace)
	{
		Result.bHit = World->SweepMultiByChannel(Result.Hits, Start, End, FQuat::Identity, TraceChannel, Shape, QueryParams);
	}
	else
	{
		FHitResult Hit;
		Result.bHit = World->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, TraceChannel, Shape, QueryParams);
		if (Result.bHit)
		{
			Result.Hits.Add(Hit);
		}
	}

	if (bDrawDebug)
	{
		DrawDebugSphere(World, End, Radius, 16, Result.bHit ? FColor::Red : FColor::Green, false, 1.0f);
	}

	return Result;
}