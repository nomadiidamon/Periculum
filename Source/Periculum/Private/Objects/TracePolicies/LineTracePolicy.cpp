// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/TracePolicies/LineTracePolicy.h"

FTracePolicyResult ULineTracePolicy::Apply_Implementation(UObject* Target) const
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
	QueryParams.bTraceComplex = bTraceComplex;

	if (bMultiTrace)
	{
		Result.bHit = World->LineTraceMultiByChannel(Result.Hits, Start, End, TraceChannel, QueryParams);
	}
	else
	{
		FHitResult Hit;
		Result.bHit = World->LineTraceSingleByChannel(Hit, Start, End, TraceChannel, QueryParams);
		if (Result.bHit)
		{
			Result.Hits.Add(Hit);
		}
	}

	if (bDrawDebug)
	{
		DrawDebugLine(World, Start, End, Result.bHit ? FColor::Red : FColor::Green, false, 1.0f);
	}

	return Result;
}
