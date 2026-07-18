// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Crosshair.h"
#include "Components/Image.h"
#include "Defines/PericulumLog.h"

void UCrosshair::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CrosshairImage)
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("CrosshairImage is not bound in Crosshair widget."));
	}
}

void UCrosshair::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!CrosshairImage)
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("CrosshairImage is not bound in Crosshair widget."));
	}
}

void UCrosshair::NativeDestruct()
{
	Super::NativeDestruct();
}


FVector2D UCrosshair::GetAbsoluteCoordinates() const
{
	if (CrosshairImage)
	{
		FGeometry Geometry = CrosshairImage->GetCachedGeometry();
		//return Geometry.GetAbsolutePosition() + Geometry.GetLocalSize() / 2;
		return Geometry.LocalToAbsolute(FVector2D(0.));
	}
	PERICULUM_LOG(Periculum_UI, Warning, TEXT("CrosshairImage is null. Cannot get absolute coordinates."));
	return FVector2D();
}

void UCrosshair::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	if (CrosshairImage)
	{
		CrosshairImage->SetVisibility(InVisibility);
	}
	else
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("CrosshairImage is null. Cannot set visibility."));
	}
}
