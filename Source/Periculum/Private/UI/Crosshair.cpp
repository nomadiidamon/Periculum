// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Crosshair.h"
#include "Components/Image.h"
#include "Defines/PericulumLog.h"

void UCrosshair::NativeConstruct()
{
	Super::NativeConstruct();
	SetCrosshairState(ECrosshairState::Default);
	if (!CurrentCrosshair)
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("CurrentCrosshair is not bound. Please check the widget blueprint."));
	}
	if (CrosshairStates.Num() < 4)
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("CrosshairStates array does not have enough elements. Please check the widget blueprint."));
	}
	if (!OnCrosshairHit.IsAlreadyBound(this, &UCrosshair::HandleCrosshairHit))
	{
		OnCrosshairHit.AddDynamic(this, &UCrosshair::HandleCrosshairHit);
	}
	if (!OnCrosshairHitAlly.IsAlreadyBound(this, &UCrosshair::HandleCrosshairHitAlly))
	{
		OnCrosshairHitAlly.AddDynamic(this, &UCrosshair::HandleCrosshairHitAlly);
	}
	if (!OnCrosshairHitEnemy.IsAlreadyBound(this, &UCrosshair::HandleCrosshairHitEnemy))
	{
		OnCrosshairHitEnemy.AddDynamic(this, &UCrosshair::HandleCrosshairHitEnemy);
	}
}

void UCrosshair::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (CurrentCrosshair)
	{
		SetCrosshairState(ECrosshairState::Default);
	}
}

void UCrosshair::NativeDestruct()
{
	Super::NativeDestruct();
	if (OnCrosshairHit.IsAlreadyBound(this, &UCrosshair::HandleCrosshairHit))
		OnCrosshairHit.RemoveDynamic(this, &UCrosshair::HandleCrosshairHit);

	if (OnCrosshairHitAlly.IsAlreadyBound(this, &UCrosshair::HandleCrosshairHitAlly))
		OnCrosshairHitAlly.RemoveDynamic(this, &UCrosshair::HandleCrosshairHitAlly);

	if (OnCrosshairHitEnemy.IsAlreadyBound(this, &UCrosshair::HandleCrosshairHitEnemy))
		OnCrosshairHitEnemy.RemoveDynamic(this, &UCrosshair::HandleCrosshairHitEnemy);
}

void UCrosshair::HandleCrosshairHit()
{
	if (!ValidCrosshairStates())
	{
		return;
	}
	SetCrosshairState(ECrosshairState::Hit);
}

void UCrosshair::HandleCrosshairHitAlly(bool bIsAlly)
{
	if (!ValidCrosshairStates())
	{
		return;
	}
	SetCrosshairState(bIsAlly ? ECrosshairState::Ally : ECrosshairState::Enemy);
}

void UCrosshair::HandleCrosshairHitEnemy(bool bIsAlly)
{
	if (!ValidCrosshairStates())
	{
		return;
	}
	SetCrosshairState(bIsAlly ? ECrosshairState::Ally : ECrosshairState::Enemy);
}

void UCrosshair::SetCrosshairState(ECrosshairState NewState)
{
	if (!ValidCrosshairStates())
	{
		return;
	}
	if (CurrentState == NewState)
	{
		return;
	}

	switch (NewState)
	{
	case ECrosshairState::Default:
		CurrentCrosshair->SetBrush(CrosshairStates[0]->GetBrush());
		break;
	case ECrosshairState::Hit:
		CurrentCrosshair->SetBrush(CrosshairStates[1]->GetBrush());
		break;
	case ECrosshairState::Ally:
		CurrentCrosshair->SetBrush(CrosshairStates[2]->GetBrush());
		break;
	case ECrosshairState::Enemy:
		CurrentCrosshair->SetBrush(CrosshairStates[3]->GetBrush());
		break;
	default:
		CurrentCrosshair->SetBrush(CrosshairStates[0]->GetBrush());
		break;
	}
}

FVector2D UCrosshair::GetAbsoluteCoordinates() const
{
	if (CurrentCrosshair)
	{
		FGeometry Geometry = CurrentCrosshair->GetCachedGeometry();
		//return Geometry.GetAbsolutePosition() + Geometry.GetLocalSize() / 2;
		return Geometry.LocalToAbsolute(FVector2D(0.));
	}
	PERICULUM_LOG(Periculum_UI, Warning, TEXT("CurrentCrosshair is null. Cannot get absolute coordinates."));
	return FVector2D();
}

void UCrosshair::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	if (CurrentCrosshair)
	{
		CurrentCrosshair->SetVisibility(InVisibility);
	}
	else
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("CurrentCrosshair is null. Cannot set visibility."));
	}
}

bool UCrosshair::ValidCrosshairStates() const
{
	if (!CurrentCrosshair || CrosshairStates.Num() == 0 || CrosshairStates.Num() < 4)
	{
		return false;
	}
	return true;
}
