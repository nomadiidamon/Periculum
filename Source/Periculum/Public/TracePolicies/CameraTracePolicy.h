// Fill out your copyright notice in the Description page of Project Settings.

/// @file CameraTracePolicy.h
/// @brief Defines the UCameraTracePolicy class, which performs traces from the camera's perspective using various trace types (line, sphere, capsule, box).

#pragma once
#include "CoreMinimal.h"
#include "TracePolicies/TracePolicy.h"
#include "Camera/CameraComponent.h"
#include "CameraTracePolicy.generated.h"


UENUM(BlueprintType)
enum class ECameraTraceType : uint8
{
	Cam_LineTrace UMETA(DisplayName = "Line Trace"),
	
	Cam_SphereTrace UMETA(DisplayName = "Sphere Trace"),

	Cam_CapsuleTrace UMETA(DisplayName = "Capsule Trace"),

	Cam_BoxTrace UMETA(DisplayName = "Box Trace")	
};


/**
 * Performs a trace from the camera's perspective, allowing for different types of traces (line, sphere, capsule, box) to be executed based on the specified trace type.
 * This policy can be used to detect objects in the camera's view and is configurable with various parameters such as start and end locations, trace channel, and debug options.
 */
UCLASS(EditInlineNew, BlueprintType)
class PERICULUM_API UCameraTracePolicy : public UTracePolicy
{
	GENERATED_BODY()

public:	
	/// <summary>
	/// The type of trace to perform from the camera's perspective. This can be a line trace, sphere trace, capsule trace, or box trace, allowing for different collision detection methods based on the needs of the user.
	/// </summary>
	UPROPERTY()
	ECameraTraceType CameraTraceType = ECameraTraceType::Cam_LineTrace;

	/// <summary>
	/// Reference to the camera component to trace from. The trace will automatically use the camera's current location and rotation.
	/// </summary>
	UPROPERTY()
	TWeakObjectPtr<UCameraComponent> CameraComponent;

	/// <summary>
	/// The local-space offset from the camera's location to begin the trace.
	/// </summary>
	UPROPERTY()
	FVector StartOffset = FVector::ZeroVector;

	/// <summary>
	/// The local-space offset from the camera's location to end the trace.
	/// </summary>
	UPROPERTY()
	FVector EndOffset = FVector(1000.0f, 0.0f, 0.0f);

	/// <summary>
	/// The radius of the sphere used in the sphere trace. This determines the size of the sphere that will be swept along the path defined by StartLocation and EndLocation.
	/// </summary>
	UPROPERTY()
	float SphereRadius = 25.0f;

	/// <summary>
	/// The radius of the capsule used in the capsule trace. This determines the size of the capsule that will be swept along the path defined by StartLocation and EndLocation.
	/// </summary>
	UPROPERTY()
	float CapsuleRadius = 25.0f;

	/// <summary>
	/// The half-height of the capsule used in the capsule trace. This defines the vertical extent of the capsule, allowing for a taller or shorter collision shape to be used in the trace.
	/// </summary>
	UPROPERTY()
	float CapsuleHalfHeight = 50.0f;

	/// <summary>
	/// The half extents of the box used in the box trace. This defines the size of the box in each dimension (X, Y, Z) and determines how large the box will be when performing the trace.
	/// </summary>
	UPROPERTY()
	FVector3f BoxHalfExtent = FVector3f(50.0f, 50.0f, 50.0f);

	/// <summary>
	/// The collision channel to use for the sphere trace. This defines what types of objects the trace will interact with, based on their collision settings.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	/// <summary>
	/// Whether to trace against complex collision (triangles) or simple collision (primitives). Complex collision is more accurate but can be more expensive, while simple collision is faster but less precise.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LineTracePolicy")
	bool bLineTraceComplex = false;

	/// <summary>
	/// Whether to trace against complex collision. If true, the trace will consider the detailed geometry of objects; if false, it will use simplified collision shapes.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	bool bMultiTrace = false;

	/// <summary>
	/// Whether to draw debug lines for the sphere trace. If true, visual debug information will be rendered in the game world to show the path and results of the trace.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereTracePolicy")
	bool bDrawDebug = false;

	virtual FTracePolicyResult Apply_Implementation(UObject* Target) const override;
};
