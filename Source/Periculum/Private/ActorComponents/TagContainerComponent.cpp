// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/TagContainerComponent.h"

UTagContainerComponent::UTagContainerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTagContainerComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTagContainerComponent::AddTag(FGameplayTag Tag, int32 Count)
{
	int32& StackCount = TagStackCounts.FindOrAdd(Tag);
	StackCount += Count;

	if (StackCount > 0)
	{
		GameplayTags.AddTag(Tag);
		HandleTagAdded(Tag);
	}
}

void UTagContainerComponent::RemoveTag(FGameplayTag Tag, int32 Count)
{
	if (int32* StackCountPtr = TagStackCounts.Find(Tag))
	{
		int32& StackCount = *StackCountPtr;
		StackCount -= Count;
		if (StackCount <= 0)
		{
			GameplayTags.RemoveTag(Tag);
			HandleTagRemoved(Tag);
			TagStackCounts.Remove(Tag);
		}
	}
}

bool UTagContainerComponent::HasTag(FGameplayTag Tag) const
{
	if (GameplayTags.HasTag(Tag))
	{
		return true;
	}
	return false;
}

bool UTagContainerComponent::HasAnyTag(const FGameplayTagContainer& TagContainer) const
{
	return GameplayTags.HasAny(TagContainer);
}

bool UTagContainerComponent::HasAllTags(const FGameplayTagContainer& TagContainer) const
{
	return GameplayTags.HasAll(TagContainer);
}

int32 UTagContainerComponent::GetTagStackCount(FGameplayTag Tag) const
{
	return TagStackCounts.Contains(Tag) ? TagStackCounts[Tag] : 0;
}

void UTagContainerComponent::ClearStack(FGameplayTag TagToClear)
{
	if (TagStackCounts.Contains(TagToClear))
	{
		int32 maxCount = TagStackCounts[TagToClear];
		RemoveTag(TagToClear, maxCount);
	}
}

void UTagContainerComponent::ClearAllStacks()
{
	for (const auto& Pair : TagStackCounts)
	{
		RemoveTag(Pair.Key, Pair.Value);
	}
	TagStackCounts.Empty();
}

void UTagContainerComponent::HandleTagAdded(FGameplayTag Tag)
{
	if (OnTagAdded.IsBound())
	{
		OnTagAdded.Broadcast(Tag);
	}
}

void UTagContainerComponent::HandleTagRemoved(FGameplayTag Tag)
{
	if (OnTagRemoved.IsBound())
	{
		OnTagRemoved.Broadcast(Tag);
	}
}

