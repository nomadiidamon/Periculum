// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TogglePolicies/TogglePolicy.h"
#include "MaterialParameterTogglePolicy.generated.h"

/**
 * The type of material parameter to modify.
 */
UENUM(BlueprintType)
enum class EMaterialParamType : uint8
{
    Scalar  UMETA(DisplayName = "Scalar"),
    Color   UMETA(DisplayName = "Linear Color"),
    Vector  UMETA(DisplayName = "Vector (XYZ)"),
};


/**
 * A toggle policy that modifies a material parameter.
 */
UCLASS()
class PERICULUM_API UMaterialParameterTogglePolicy : public UTogglePolicy
{
	GENERATED_BODY()
	
public:
    /// <summary>
	/// The name of the material parameter to modify. This should match the name of a parameter in the material applied to the target object.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter")
    FName ParameterName = NAME_None;

    /// <summary>
	/// The type of the material parameter to modify. This determines which property of the material will be changed when the policy is applied.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter")
    EMaterialParamType ParameterType = EMaterialParamType::Scalar;

    /// <summary>
	/// The value to set the material parameter to when the policy is applied and the target is enabled. This value is used for scalar parameters.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Scalar",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Scalar", EditConditionHides))
    float EnabledScalar = 1.0f;

    /// <summary>
	/// The value to set the material parameter to when the policy is applied and the target is disabled. This value is used for scalar parameters.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Scalar",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Scalar", EditConditionHides))
    float DisabledScalar = 0.0f;

    /// <summary>
	/// The Linear Color value to set the material parameter to when the policy is applied and the target is enabled. This value is used for color parameters.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Color",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Color", EditConditionHides))
    FLinearColor EnabledColor = FLinearColor::White;

    /// <summary>
	/// The Linear Color value to set the material parameter to when the policy is applied and the target is disabled. This value is used for color parameters.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Color",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Color", EditConditionHides))
    FLinearColor DisabledColor = FLinearColor::Black;

    /// <summary>
	/// The Vector value to set the material parameter to when the policy is applied and the target is enabled. This value is used for vector parameters.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Vector",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Vector", EditConditionHides))
    FLinearColor EnabledVector = FLinearColor(1.f, 1.f, 1.f, 1.f);

    /// <summary>
	/// THe Vector value to set the material parameter to when the policy is applied and the target is disabled. This value is used for vector parameters.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaterialParameter|Vector",
        meta = (EditCondition = "ParameterType == EMaterialParamType::Vector", EditConditionHides))
    FLinearColor DisabledVector = FLinearColor(0.f, 0.f, 0.f, 0.f);

    virtual bool CanApply_Implementation(UObject* Target, bool bEnable) override;
    virtual void Apply_Implementation(UObject* Target, bool bEnable) override;
};
