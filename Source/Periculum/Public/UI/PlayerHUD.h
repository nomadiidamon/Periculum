#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair.h"
#include "PlayerHUD.generated.h"


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

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UHealthBar> PlayerHealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCrosshair> HUDCrosshair;

	UPROPERTY(EditAnywhere, Category = "HUD")
	ECrosshairState CrosshairState = ECrosshairState::Default;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TMap<ECrosshairState, UTexture2D*> CrosshairTextures;

	UPROPERTY(EditAnywhere, Category = "HUD")
	FLinearColor OriginalCrosshairColor = FLinearColor::White;

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
