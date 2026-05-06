#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */

class UHealthBar;
class UCrosshair;

UCLASS()
class PERICULUM_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


public:
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	UFUNCTION()
	void AbsoluteToViewport(UObject* WorldContextObject, FVector2D AbsoluteDesktopCoordinate, FVector2D& PixelPosition, FVector2D& ViewportPosition) const;

	UFUNCTION(BlueprintCallable)
	bool DeprojectScreenToWorld(APlayerController const* Player, const FVector2D& ScreenPosition, FVector& WorldPosition, FVector& WorldDirection) const;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UHealthBar* PlayerHealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCrosshair* Crosshair;

private:

	UPROPERTY(EditAnywhere, Category = "HUD")
	bool bFadeInAndOut;

	UPROPERTY(EditAnywhere, Category = "HUD")
	UWidgetAnimation* FadeInAnimation;

	UPROPERTY(EditAnywhere, Category = "HUD")
	UWidgetAnimation* FadeOutAnimation;

	FVector CrosshairWorldHitLocation;
};
