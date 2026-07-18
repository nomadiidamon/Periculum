// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair.generated.h"


class UImage;
/**
 * 
 */

UENUM(BlueprintType) 
enum class ECrosshairState : uint8
{
	None UMETA(DisplayName = "None"),
	Default UMETA(DisplayName = "Default"),
	Hit UMETA(DisplayName = "Hit"),
	Ally UMETA(DisplayName = "Ally"),
	Enemy UMETA(DisplayName = "Enemy"),
};


UCLASS()
class PERICULUM_API UCrosshair : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FVector2D GetAbsoluteCoordinates() const;

	void SetVisibility(ESlateVisibility InVisibility) override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* CrosshairImage;
};
