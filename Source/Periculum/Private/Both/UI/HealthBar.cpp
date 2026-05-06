// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/UI/HealthBar.h"
#include "Components/ProgressBar.h"
#include "Periculum/Periculum.h"

void UHealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	if (CurrentHealth < MinHealth)
		CurrentHealth = MinHealth;
	else if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;

	if (!OnMaxHealthChanged.IsAlreadyBound(this, &UHealthBar::SetMaxHealth))
		OnMaxHealthChanged.AddDynamic(this, &UHealthBar::SetMaxHealth);

	if (!OnMinHealthChanged.IsAlreadyBound(this, &UHealthBar::SetMinHealth))
		OnMinHealthChanged.AddDynamic(this, &UHealthBar::SetMinHealth);

	if (!OnCurrentHealthChanged.IsAlreadyBound(this, &UHealthBar::SetCurrentHealth))
		OnCurrentHealthChanged.AddDynamic(this, &UHealthBar::SetCurrentHealth);
}

void UHealthBar::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (HealthProgressBar)
	{
		HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);
		HealthProgressBar->SetBarFillStyle(EProgressBarFillStyle::Scale);
		HealthProgressBar->SetPercent(GetHealthPercent());
	}

}

void UHealthBar::NativeDestruct()
{
	Super::NativeDestruct();
	if (OnMaxHealthChanged.IsAlreadyBound(this, &UHealthBar::SetMaxHealth))
		OnMaxHealthChanged.RemoveDynamic(this, &UHealthBar::SetMaxHealth);
	if (OnMinHealthChanged.IsAlreadyBound(this, &UHealthBar::SetMinHealth))
		OnMinHealthChanged.RemoveDynamic(this, &UHealthBar::SetMinHealth);
	if (OnCurrentHealthChanged.IsAlreadyBound(this, &UHealthBar::SetCurrentHealth))
		OnCurrentHealthChanged.RemoveDynamic(this, &UHealthBar::SetCurrentHealth);
}

void UHealthBar::SetMaxHealth(float NewMaxHealth)
{
	if (NewMaxHealth <= MinHealth)
	{
		UE_LOG(HUD, Warning, TEXT("MaxHealth must be greater than MinHealth. MaxHealth not updated."));
		return;
	}
	MaxHealth = NewMaxHealth;
	SetHealthBarFromValues();
}

void UHealthBar::SetCurrentHealth(float NewCurrentHealth)
{
	if (NewCurrentHealth < MinHealth)
	{
		UE_LOG(HUD, Warning, TEXT("CurrentHealth cannot be less than MinHealth. CurrentHealth not updated."));
		return;
	}
	else if (NewCurrentHealth > MaxHealth)
	{
		UE_LOG(HUD, Warning, TEXT("CurrentHealth cannot be greater than MaxHealth. CurrentHealth not updated."));
		return;
	}
	CurrentHealth = NewCurrentHealth;
	SetHealthBarFromValues();
}

void UHealthBar::SetMinHealth(float NewMinHealth)
{
	if (NewMinHealth >= MaxHealth)
	{
		UE_LOG(HUD, Warning, TEXT("MinHealth must be less than MaxHealth. MinHealth not updated."));
		return;
	}
	MinHealth = NewMinHealth;
	SetHealthBarFromValues();
}

void UHealthBar::SetHealthBarFromValues()
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(GetHealthPercent());
	}
}

void UHealthBar::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
	SetVisibility(InVisibility);
}
