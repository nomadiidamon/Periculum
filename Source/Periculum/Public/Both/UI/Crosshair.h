// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCrosshairEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCrosshairCharacterEvent, bool, bIsAlly);


class UImage;
/**
 * 
 */

UENUM(BlueprintType) 
enum class ECrosshairState : uint8
{
	Default UMETA(DisplayName = "Default"),
	Hit UMETA(DisplayName = "Hit"),
	Ally UMETA(DisplayName = "Ally"),
	Enemy UMETA(DisplayName = "Enemy")
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

	UPROPERTY(BlueprintAssignable)
	FOnCrosshairEvent OnCrosshairHit;

	UPROPERTY(BlueprintAssignable)
	FOnCrosshairCharacterEvent OnCrosshairHitAlly;

	UPROPERTY(BlueprintAssignable)
	FOnCrosshairCharacterEvent OnCrosshairHitEnemy;

	UFUNCTION(BlueprintCallable)
	virtual void HandleCrosshairHit();

	UFUNCTION(BlueprintCallable)
	virtual void HandleCrosshairHitAlly(bool bIsAlly);

	UFUNCTION(BlueprintCallable)
	virtual void HandleCrosshairHitEnemy(bool bIsAlly);

	UFUNCTION(BlueprintCallable)
	void SetCrosshairState(ECrosshairState NewState);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FVector2D GetAbsoluteCoordinates() const;

	void SetVisibility(ESlateVisibility InVisibility) override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool ValidCrosshair() const { return ValidCrosshairStates(); }

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* CurrentCrosshair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair")
	TArray<UImage*> CrosshairStates;

	UPROPERTY(EditAnywhere, Category = "Crosshair")
	ECrosshairState CurrentState;

private:
	bool ValidCrosshairStates() const;
};
