#include "UI/ButtonWithText.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UButtonWithText::NativeConstruct()
{
	Super::NativeConstruct();
	if (Button)
	{
		if (!Button->OnClicked.IsAlreadyBound(this, &UButtonWithText::HandleButtonClicked))
			Button->OnClicked.AddDynamic(this, &UButtonWithText::HandleButtonClicked);
		if (!Button->OnHovered.IsAlreadyBound(this, &UButtonWithText::HandleButtonHovered))
			Button->OnHovered.AddDynamic(this, &UButtonWithText::HandleButtonHovered);
	}
}

void UButtonWithText::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (TextBlock)
	{
		TextBlock->SetText(Info);
	}
}

void UButtonWithText::NativeDestruct()
{
	Super::NativeDestruct();
	if (Button)
	{
		if (Button->OnClicked.IsAlreadyBound(this, &UButtonWithText::HandleButtonClicked))
			Button->OnClicked.RemoveDynamic(this, &UButtonWithText::HandleButtonClicked);
		if (Button->OnHovered.IsAlreadyBound(this, &UButtonWithText::HandleButtonHovered))
			Button->OnHovered.RemoveDynamic(this, &UButtonWithText::HandleButtonHovered);
	}
}

void UButtonWithText::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	bIsCurrentlyFocused = true;
	HandleButtonFocused(bIsCurrentlyFocused);
}

void UButtonWithText::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
	bIsCurrentlyFocused = false;
	HandleButtonFocused(bIsCurrentlyFocused);
}

void UButtonWithText::HandleButtonClicked()
{
	if (OnClicked.IsBound())
		OnClicked.Broadcast();
}

void UButtonWithText::HandleButtonHovered()
{
	if (OnHovered.IsBound())
		OnHovered.Broadcast();
}

void UButtonWithText::HandleButtonFocused(bool bIsFocused)
{
	if (OnFocused.IsBound())
		OnFocused.Broadcast(bIsFocused);
}

void UButtonWithText::SetInfoText(const FText& InInfo)
{
	Info = InInfo;
	if (TextBlock)
	{
		TextBlock->SetText(Info);
	}
}