// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "TagContainerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagAdded, FGameplayTag, Tag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagRemoved, FGameplayTag, Tag);

/**
 * This component allows an actor to have a container of gameplay tags that can be added or removed at runtime. 
 * It also supports tag stacking, where multiple instances of the same tag can be added and removed independently.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PERICULUM_API UTagContainerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTagContainerComponent();
	virtual void BeginPlay() override;

public:
	/// <summary>
	/// Dynamic multicast delegate that is broadcast when a tag is added to the container. Listeners can bind to this event to react to tag additions.
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "Tags")
	FOnTagAdded OnTagAdded;

	/// <summary>
	/// Dynamic multicast delegate that is broadcast when a tag is removed from the container. Listeners can bind to this event to react to tag removals.
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "Tags")
	FOnTagRemoved OnTagRemoved;

protected:
	/// The container of gameplay tags that this component manages.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer GameplayTags;

	/// A map that keeps track of the stack count for each tag. The key is the tag, and the value is the count.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	TMap<FGameplayTag, int32> TagStackCounts;

public:
	/// <summary>
	/// Adds the specified tag to the container. If the tag already exists, it increments its stack count by the specified amount.
	/// </summary>
	/// <param name="Tag">The tag to add.</param>
	/// <param name="Count">The number of instances to add.</param>
	UFUNCTION(BlueprintCallable, Category = "Tags")
	void AddTag(FGameplayTag Tag, int32 Count = 1);

	/// <summary>
	/// Removes the specified tag from the container. If the tag has a stack count greater than one, it decrements the count by the specified amount. If the count reaches zero, the tag is removed entirely.
	/// </summary>
	/// <param name="Tag">The tag to remove.</param>
	/// <param name="Count">The number of instances to remove.</param>
	UFUNCTION(BlueprintCallable, Category = "Tags")
	void RemoveTag(FGameplayTag Tag, int32 Count = 1);

	/// <summary>
	/// Checks if the container has the specified tag, regardless of its stack count.
	/// </summary>
	/// <param name="Tag">The tag to check for.</param>
	/// <returns>True if the tag is present, false otherwise.</returns>
	UFUNCTION(BlueprintCallable, Category = "Tags")
	bool HasTag(FGameplayTag Tag) const;

	/// <summary>
	/// Checks if the container has any of the tags in the specified tag container, regardless of their stack counts.
	/// </summary>
	/// <param name="TagContainer">The tag container to check against.</param>
	/// <returns>True if any tags are present, false otherwise.</returns>
	UFUNCTION(BlueprintCallable, Category = "Tags")
	bool HasAnyTag(const FGameplayTagContainer& TagContainer) const;

	/// <summary>
	/// Checks if the container has all of the tags in the specified tag container, regardless of their stack counts.
	/// </summary>
	/// <param name="TagContainer">The tag container to check against.</param>
	/// <returns>True if all tags are present, false otherwise.</returns>
	UFUNCTION(BlueprintCallable, Category = "Tags")
	bool HasAllTags(const FGameplayTagContainer& TagContainer) const;

	/// <summary>
	/// Retrieves the current stack count for the specified tag. If the tag is not present, it returns zero.
	/// </summary>
	/// <param name="Tag">The tag to check.</param>
	/// <returns>The current stack count for the tag.</returns>
	UFUNCTION(BlueprintCallable, Category = "Tags")
	int32 GetTagStackCount(FGameplayTag Tag) const;

	/// <summary>
	/// Reduces the stack count of the specified tag to zero and removes it from the container entirely, regardless of its current count.
	/// </summary>
	/// <param name="TagToClear">The tag to clear.</param>
	UFUNCTION(BlueprintCallable, Category = "Tags")
	void ClearStack(FGameplayTag TagToClear);

	/// <summary>
	/// Removes all tags from the container and resets their stack counts to zero.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Tags")
	void ClearAllStacks();

protected:
	/// <summary>
	/// Internally broadcasts to those listening that a tag has been added to the container. This is called after the tag is successfully added.
	/// </summary>
	/// <param name="Tag"></param>
	void HandleTagAdded(FGameplayTag Tag);

	/// <summary>
	/// Internally broadcasts to those listening that a tag has been removed from the container. This is called after the tag is successfully removed.
	/// </summary>
	/// <param name="Tag"></param>
	void HandleTagRemoved(FGameplayTag Tag);
};
