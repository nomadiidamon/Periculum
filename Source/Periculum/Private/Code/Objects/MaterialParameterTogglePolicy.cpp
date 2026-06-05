// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Objects/MaterialParameterTogglePolicy.h"

bool UMaterialParameterTogglePolicy::CanApply_Implementation(UObject* Target, bool bEnable)
{
    return ParameterName != NAME_None;
}

void UMaterialParameterTogglePolicy::Apply_Implementation(UObject* Target, bool bEnable)
{
    AActor* Actor = Cast<AActor>(Target);
    if (!Actor)
    {
        return;
    }

    TArray<UMeshComponent*> Meshes;
    Actor->GetComponents<UMeshComponent>(Meshes);

    for (UMeshComponent* Mesh : Meshes)
    {
        if (!Mesh)
        {
            continue;
        }

        for (int32 i = 0; i < Mesh->GetNumMaterials(); ++i)
        {
            UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(i));
            if (!MID)
            {
                MID = Mesh->CreateAndSetMaterialInstanceDynamic(i);
            }
            if (!MID)
            {
                continue;
            }

            switch (ParameterType)
            {
            case EMaterialParamType::Scalar:
            {
                MID->SetScalarParameterValue(ParameterName, bEnable ? EnabledScalar : DisabledScalar);
                break;
            }
            case EMaterialParamType::Color:
            {
                MID->SetVectorParameterValue(ParameterName, bEnable ? EnabledColor : DisabledColor);
                break;
            }
            case EMaterialParamType::Vector:
            {
                MID->SetVectorParameterValue(ParameterName, bEnable ? EnabledVector : DisabledVector);
                break;
            }
            }
        }
    }
}
