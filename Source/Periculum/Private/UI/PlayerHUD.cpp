
#include "UI/PlayerHUD.h"
#include "UI/HealthBar.h"
#include "UI/Crosshair.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"

#include "Slate/SGameLayerManager.h"

#include "Defines/PericulumLog.h"


void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	if (!PlayerHealthBar)
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("PlayerHealthBar is not bound in PlayerHUD"));
	}
	if (!HUDCrosshair)
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("Crosshair is not bound in PlayerHUD"));
	}
	else {
		HUDCrosshair->CrosshairImage->SetBrushFromTexture(CrosshairTextures[CrosshairState]);
		OriginalCrosshairColor = HUDCrosshair->CrosshairImage->ColorAndOpacity;
	}


	if (bFadeInAndOut)
	{
		if (!FadeInAnimation)
		{
			PERICULUM_LOG(Periculum_UI, Warning, TEXT("FadeInAnimation is not set in PlayerHUD."));
		}
		if (!FadeOutAnimation)
		{
			PERICULUM_LOG(Periculum_UI, Warning, TEXT("FadeOutAnimation is not set in PlayerHUD."));
		}
	}
}

void UPlayerHUD::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!HUDCrosshair)
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("Crosshair is not valid in PlayerHUD. Please check the widget blueprint."));
		return;
	}

	if (!HUDCrosshair->CrosshairImage)
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("CrosshairImage is not valid in PlayerHUD. Please check the widget blueprint."));
		return;
	}

	if (!CrosshairTextures.Contains(CrosshairState))
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("CrosshairTextures does not contain the current CrosshairState in PlayerHUD."));
		return;
	}
	HUDCrosshair->CrosshairImage->SetBrushFromTexture(CrosshairTextures[CrosshairState]);

}

void UPlayerHUD::NativeDestruct()
{
	Super::NativeDestruct();

}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPlayerHUD::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);

	if (bFadeInAndOut)
	{
		if (InVisibility == ESlateVisibility::Visible)
		{
			if (!FadeInAnimation)
			{
				PERICULUM_LOG(Periculum_UI, Warning, TEXT("FadeInAnimation is not set in PlayerHUD."));
				return;
			}
			PlayAnimation(FadeInAnimation);
		}
		else
		{
			if (!FadeOutAnimation)
			{
				PERICULUM_LOG(Periculum_UI, Warning, TEXT("FadeOutAnimation is not set in PlayerHUD."));
				return;
			}
			PlayAnimation(FadeOutAnimation);
		}
	}
}


void UPlayerHUD::SetCrosshairState(ECrosshairState NewState)
{
	if (!HUDCrosshair)
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("Crosshair is null. Cannot set crosshair state."));
		return;
	}

	HUDCrosshair->SetVisibility(ESlateVisibility::Hidden);

	UTexture2D* crosshairTexture = CrosshairTextures.Contains(NewState) ? CrosshairTextures[NewState] : nullptr;

	HUDCrosshair->CrosshairImage->SetBrushFromTexture(crosshairTexture);

	if (NewState == ECrosshairState::Hit) {
		HUDCrosshair->CrosshairImage->SetColorAndOpacity(FLinearColor::Red);
	}
	else if (NewState == ECrosshairState::Ally) {
		HUDCrosshair->CrosshairImage->SetColorAndOpacity(FLinearColor::Green);
	}
	else if (NewState == ECrosshairState::Enemy) {
		HUDCrosshair->CrosshairImage->SetColorAndOpacity(FLinearColor::Red);
	}
	else {
		HUDCrosshair->CrosshairImage->SetColorAndOpacity(OriginalCrosshairColor);
	}

	HUDCrosshair->SetVisibility(ESlateVisibility::Visible);
}
