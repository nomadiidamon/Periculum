#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair.h"
#include "PlayerHUD.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCrosshairEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCrosshairCharacterEvent, bool, bIsAlly);

class UHealthBar;
class UCrosshair;

/**
 * 
 */
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
	TObjectPtr<UHealthBar> PlayerHealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCrosshair> HUDCrosshair;

	UPROPERTY(EditAnywhere, Category = "HUD")
	ECrosshairState CrosshairState = ECrosshairState::Default;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TMap<ECrosshairState, UTexture2D*> CrosshairTextures;

	UPROPERTY(BlueprintAssignable)
	FOnCrosshairEvent OnCrosshairHit;

	UPROPERTY(BlueprintAssignable)
	FOnCrosshairCharacterEvent OnCrosshairHitAlly;

	UPROPERTY(BlueprintAssignable)
	FOnCrosshairCharacterEvent OnCrosshairHitEnemy;

	UFUNCTION(BlueprintCallable)
	void SetCrosshairState(ECrosshairState NewState);

	UFUNCTION(BlueprintCallable)
	FVector GetCrosshairWorldLocation() const {	return CrossHairWorldLocation; }
private:

	UPROPERTY(EditAnywhere, Category = "HUD")
	bool bFadeInAndOut;

	UPROPERTY(EditAnywhere, Category = "HUD")
	UWidgetAnimation* FadeInAnimation;

	UPROPERTY(EditAnywhere, Category = "HUD")
	UWidgetAnimation* FadeOutAnimation;

	FVector CrosshairWorldHitLocation;

	FVector CrossHairWorldLocation;
};
