#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWithText.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonFocused, bool, bIsFocused);

/**
 * 
 */

class UButton;
class UTextBlock;

UCLASS()
class PERICULUM_API UButtonWithText : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	virtual void NativeDestruct() override;

	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;

	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonClicked OnClicked;

	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonHovered OnHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonFocused OnFocused;

	UFUNCTION(BlueprintCallable)
	virtual void HandleButtonClicked();

	UFUNCTION(BlueprintCallable)
	virtual void HandleButtonHovered();

	UFUNCTION(BlueprintCallable)
	virtual void HandleButtonFocused(bool bIsFocused);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsFocused() const { return bIsCurrentlyFocused; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Button")
	bool bIsCurrentlyFocused;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	FText Info;

	UPROPERTY(BlueprintReadOnly, Category = "BindWidget")
	UButton* Button;

	UPROPERTY(BlueprintReadOnly, Category = "BindWidget")
	UTextBlock* TextBlock;

public:
	UFUNCTION(BlueprintCallable, Category = "Button")
	virtual void SetInfoText(const FText& InInfo);
	
};
