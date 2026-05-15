
#include "Both/UI/PlayerHUD.h"
#include "Both/UI/HealthBar.h"
#include "Both/UI/Crosshair.h"

#include "Slate/SGameLayerManager.h"

#include "Code/Utility/PericulumLog.h"


void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	if (!PlayerHealthBar)
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("PlayerHealthBar is not bound in PlayerHUD"));
	}
	if (!Crosshair)
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("Crosshair is not bound in PlayerHUD"));
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

}

void UPlayerHUD::NativeDestruct()
{
	Super::NativeDestruct();

}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!Crosshair || !Crosshair->ValidCrosshair())
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("Crosshair is not valid in PlayerHUD. Please check the widget blueprint."));
		return;
	}

	FVector2D PixelPosition, ViewportPosition;
	FVector2D AbsoluteCoordinates = Crosshair->GetAbsoluteCoordinates();
	AbsoluteToViewport(this->GetOwningPlayer(), AbsoluteCoordinates, PixelPosition, ViewportPosition);

	FVector WorldPosition, WorldDirection;
	if (!DeprojectScreenToWorld(this->GetOwningPlayer(),
		PixelPosition + (TransformVector(Crosshair->GetCachedGeometry().GetAccumulatedRenderTransform(),
			Crosshair->GetCachedGeometry().GetLocalSize()) * 0.5f), WorldPosition, WorldDirection))
	{
		PERICULUM_LOG(Periculum_UI, Warning, TEXT("Failed to deproject screen to world in PlayerHUD."));
	}

	CrosshairWorldHitLocation = WorldPosition + WorldDirection * 100000.f;
	FHitResult hit;
	if (GetWorld()->LineTraceSingleByObjectType(hit, WorldPosition, CrosshairWorldHitLocation,
		FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_Pawn) | ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)),
		FCollisionQueryParams(FName(TEXT("CrosshairTrace")), false, this->GetOwningPlayer())))
	{
		CrosshairWorldHitLocation = hit.ImpactPoint;
		if (hit.Component->GetCollisionObjectType() == ECC_Pawn)
		{
			if (hit.GetActor()->Tags.Contains(FName(TEXT("Ally"))))
			{
				Crosshair->SetCrosshairState(ECrosshairState::Ally);
				PERICULUM_LOG(Periculum_UI, Log, TEXT("Crosshair hit ally at location: %s"), *CrosshairWorldHitLocation.ToString());
			}
			else if (hit.GetActor()->Tags.Contains(FName(TEXT("Enemy"))))
			{
				Crosshair->SetCrosshairState(ECrosshairState::Enemy);
				PERICULUM_LOG(Periculum_UI, Log, TEXT("Crosshair hit enemy at location: %s"), *CrosshairWorldHitLocation.ToString());
			}
			else 
			{
				Crosshair->SetCrosshairState(ECrosshairState::Hit);
			}

		}
		else if (hit.Component->GetCollisionObjectType() == ECC_WorldStatic || hit.Component->GetCollisionObjectType() == ECC_WorldDynamic)
		{
			Crosshair->SetCrosshairState(ECrosshairState::Default);
			PERICULUM_LOG(Periculum_UI, Log, TEXT("Crosshair hit world at location: %s"), *CrosshairWorldHitLocation.ToString());
		}
	}
	else {
		Crosshair->SetCrosshairState(ECrosshairState::Default);
	}

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

void UPlayerHUD::AbsoluteToViewport(UObject* WorldContextObject, FVector2D AbsoluteDesktopCoordinate, FVector2D& PixelPosition, FVector2D& ViewportPosition) const
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World && World->IsGameWorld())
	{
		if (UGameViewportClient* ViewportClient = World->GetGameViewport())
		{
			TSharedPtr<IGameLayerManager> GameLayerManager = ViewportClient->GetGameLayerManager();
			if (GameLayerManager.IsValid())
			{
				FVector2D ViewportSize;
				ViewportClient->GetViewportSize(ViewportSize);

				const FGeometry& ViewportGeometry = GameLayerManager->GetViewportWidgetHostGeometry();

				ViewportPosition = ViewportGeometry.AbsoluteToLocal(AbsoluteDesktopCoordinate);
				PixelPosition = (ViewportPosition / ViewportGeometry.GetLocalSize()) * ViewportSize;

				return;
			}
		}
	}

	PixelPosition = FVector2D(0, 0);
	ViewportPosition = FVector2D(0, 0);
}

bool UPlayerHUD::DeprojectScreenToWorld(APlayerController const* Player, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection) const
{
	ULocalPlayer* const LP = Player ? Player->GetLocalPlayer() : nullptr;
	if (LP && LP->ViewportClient)
	{
		FSceneViewProjectionData ProjectionData;
		if (LP->GetProjectionData(LP->ViewportClient->Viewport, /*out*/ ProjectionData))
		{
			FMatrix const InvViewProjMatrix = ProjectionData.ComputeViewProjectionMatrix().InverseFast();
			FSceneView::DeprojectScreenToWorld(ScreenPosition, ProjectionData.GetConstrainedViewRect(), InvViewProjMatrix, /*out*/ WorldPosition, /*out*/ WorldDirection);
			return true;
		}
	}

	WorldPosition = FVector::ZeroVector;
	WorldDirection = FVector::ZeroVector;
	return false;
}
