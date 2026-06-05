// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Objects/TogglePolicy.h"
#include "MaterialParameterTogglePolicy.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMaterialParamType : uint8
{
    Scalar  UMETA(DisplayName = "Scalar"),
    Color   UMETA(DisplayName = "Linear Color"),
    Vector  UMETA(DisplayName = "Vector (XYZ)"),
};


UCLASS()
class PERICULUM_API UMaterialParameterTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter")
    FName ParameterName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter")
    EMaterialParamType ParameterType = EMaterialParamType::Scalar;

    // --- Scalar ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Scalar",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Scalar", EditConditionHides))
    float EnabledScalar = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Scalar",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Scalar", EditConditionHides))
    float DisabledScalar = 0.0f;

    // --- Linear Color ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Color",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Color", EditConditionHides))
    FLinearColor EnabledColor = FLinearColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Color",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Color", EditConditionHides))
    FLinearColor DisabledColor = FLinearColor::Black;

    // --- Vector ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Vector",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Vector", EditConditionHides))
    FLinearColor EnabledVector = FLinearColor(1.f, 1.f, 1.f, 1.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Vector",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Vector", EditConditionHides))
    FLinearColor DisabledVector = FLinearColor(0.f, 0.f, 0.f, 0.f);

    virtual bool CanApply_Implementation(UObject* Target, bool bEnable) override;
    virtual void Apply_Implementation(UObject* Target, bool bEnable) override;
};
