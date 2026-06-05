// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Code/Components/ToggleableComponent.h"
#include "Code/Objects/TogglePolicy.h"
#include "Code/Utility/ToggleProfile.h"
#include "ToggleStatics.generated.h"

/**
 *
 */

UCLASS()
class PERICULUM_API UToggleStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Toggle")
	static void ToggleActor(AActor* Target, bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Toggle")
	static void EnableActor(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Toggle")
	static void DisableActor(AActor* Target);

	template<typename T>
	static void ToggleComponent(T* Component, bool bEnable)
	{
		if (Component)
		{
			Component->SetActive(bEnable, true);
		}
	}

	UFUNCTION(BlueprintCallable, Category = "Toggle")
	static UToggleProfile* GetToggleProfile(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Toggle")
	static void AddPolicy(AActor* Target, UTogglePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "Toggle")
	static void AddUniquePolicy(AActor* Target, UTogglePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "Toggle")
	static void AddPolicies(AActor* Target, const TArray<UTogglePolicy*>& Policies);

	UFUNCTION(BlueprintCallable, Category = "Toggle")
	static void RemovePolicy(AActor* Target, UTogglePolicy* Policy);

	UFUNCTION(BlueprintCallable, Category = "Toggle")
	static void RemovePolicies(AActor* Target, const TArray<UTogglePolicy*>& Policies);

	UFUNCTION(BlueprintCallable, Category = "Toggle")
	static void ClearPolicies(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Toggle")
	static bool ActorIsToggleable(AActor* Target);


};
