// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/TraceStatics.h"

#include "Camera/CameraComponent.h"

#include "ActorComponents/TraceComponent.h"

#include "TracePolicies/SphereTracePolicy.h"
#include "TracePolicies/CameraTracePolicy.h"


FTraceResult UTraceStatics::PerformTrace(AActor* Target)
{
	if (!Target)
	{
		return FTraceResult();
	}
	if (UTraceComponent* TraceComp = Cast<UTraceComponent>(Target->GetComponentByClass(UTraceComponent::StaticClass())))
	{
		return TraceComp->PerformTrace();
	}
	return FTraceResult();
}

FTracePolicyResult UTraceStatics::PerformTraceByTag(AActor* Target, FName Tag)
{
	if (!Target)
	{
		return FTracePolicyResult();
	}
	if (UTraceComponent* TraceComp = Cast<UTraceComponent>(Target->GetComponentByClass(UTraceComponent::StaticClass())))
	{
		return TraceComp->PerformTraceByTag(Tag);
	}
	return FTracePolicyResult();
}

UTraceProfile* UTraceStatics::GetTraceProfile(AActor* Target)
{
	if (!Target)
	{
		return nullptr;
	}
	if (UTraceComponent* TraceComp = Cast<UTraceComponent>(Target->GetComponentByClass(UTraceComponent::StaticClass())))
	{
		return TraceComp->GetActiveProfile();
	}
	return nullptr;
}

void UTraceStatics::AddPolicy(AActor* Target, UTracePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->AddPolicy(Policy);
		}
	}
}

void UTraceStatics::AddUniquePolicy(AActor* Target, UTracePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->AddUniquePolicy(Policy);
		}
	}
}


void UTraceStatics::AddPolicies(AActor* Target, const TArray<UTracePolicy*>& Policies)
{
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->AddPolicies(Policies);
		}
	}
}

void UTraceStatics::RemovePolicy(AActor* Target, UTracePolicy* Policy) {
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->RemovePolicy(Policy);
		}
	}
}

void UTraceStatics::RemovePolicies(AActor* Target, const TArray<UTracePolicy*>& Policies)
{
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->RemovePolicies(Policies);
		}
	}
}

void UTraceStatics::ClearPolicies(AActor* Target)
{
	if (!Target)
	{
		return;
	}
	if (ActorIsTraceable(Target))
	{
		if (UTraceProfile* Profile = GetTraceProfile(Target))
		{
			Profile->ClearPolicies();
		}
	}
}

bool UTraceStatics::ActorIsTraceable(AActor* Target)
{
	if (!Target)
	{
		return false;
	}
	
	return Target->FindComponentByClass<UTraceComponent>() != nullptr;
}

USphereTracePolicy* UTraceStatics::MakeSphereTracePolicy(FVector StartOffset, FVector EndOffset, float Radius, ECollisionChannel TraceChannel, bool bMultiTrace, bool bDrawDebug, FName PolicyName, EPolicyStackPriority StackPriority, int32 PriorityScalar)
{
	USphereTracePolicy* NewPolicy = NewObject<USphereTracePolicy>();
	NewPolicy->StartOffset = StartOffset;
	NewPolicy->EndOffset = EndOffset;
	NewPolicy->Radius = Radius;
	NewPolicy->TraceChannel = TraceChannel;
	NewPolicy->bMultiTrace = bMultiTrace;
	NewPolicy->bDrawDebug = bDrawDebug;
	NewPolicy->PolicyTag = PolicyName;
	NewPolicy->PolicyStackPriority = StackPriority;
	NewPolicy->PriorityScalar = PriorityScalar;

	return NewPolicy;
}

UCameraTracePolicy* UTraceStatics::MakeCameraTracePolicy(ECameraTraceType TraceType, UCameraComponent* CameraComponent, FVector StartOffset, FVector EndOffset, float SphereRadius, float CapsuleRadius, float CapsuleHalfHeight, FVector BoxHalfSize, ECollisionChannel TraceChannel, bool bMultiTrace, bool bDrawDebug, FName PolicyName, EPolicyStackPriority StackPriority, int32 PriorityScalar)
{
	UCameraTracePolicy* NewPolicy = NewObject<UCameraTracePolicy>();
	NewPolicy->CameraTraceType = TraceType;
	NewPolicy->CameraComponent = CameraComponent;
	NewPolicy->StartOffset = StartOffset;
	NewPolicy->EndOffset = EndOffset;
	NewPolicy->SphereRadius = SphereRadius;
	NewPolicy->CapsuleRadius = CapsuleRadius;
	NewPolicy->CapsuleHalfHeight = CapsuleHalfHeight;
	NewPolicy->BoxHalfExtent = FVector3f(BoxHalfSize.X, BoxHalfSize.Y, BoxHalfSize.Z);
	NewPolicy->TraceChannel = TraceChannel;
	NewPolicy->bMultiTrace = bMultiTrace;
	NewPolicy->bDrawDebug = bDrawDebug;
	NewPolicy->PolicyTag = PolicyName;
	NewPolicy->PolicyStackPriority = StackPriority;
	NewPolicy->PriorityScalar = PriorityScalar;

	return NewPolicy;
}
