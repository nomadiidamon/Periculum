// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Objects/TogglePolicy.h"


bool UTogglePolicy::CanApply_Implementation(UObject* Target, bool& bEnable)
{
	return true;
}

void UTogglePolicy::Apply_Implementation(UObject* Target, bool& bEnable)
{
}