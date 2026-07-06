// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealthPercent);

class UProgressBar;

/**
 * 
 */
UCLASS()
class PERICULUM_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	virtual void NativeDestruct() override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnMinHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnCurrentHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetMaxHealth(float NewMaxHealth);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetCurrentHealth(float NewCurrentHealth);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetMinHealth(float NewMinHealth);

	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE float GetHealthPercent() const { return (CurrentHealth - MinHealth) / (MaxHealth - MinHealth); }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealthBarFromValues();

	void SetVisibility(ESlateVisibility InVisibility) override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Health", meta = (BindWidget))
	UProgressBar* HealthProgressBar;

protected:
	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Health")
	float CurrentHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MinHealth = 0.f;

	UPROPERTY(EditAnywhere, Category = "Health")
	FLinearColor HealthBarColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, Category = "Health")
	FLinearColor BackgroundColor = FLinearColor::Black;

	
};
