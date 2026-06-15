// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Characters/CharacterProfileTypes.h"
#include "Progression/SkillTreeTypes.generated.h"

UENUM(BlueprintType)
enum class ESkillNodeRewardType : uint8
{
	StatBonus,
	AbilityUnlock,
	AbilityUpgrade,
	WeaponProficiency
};

USTRUCT(BlueprintType)
struct FSkillTreeNode
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName NodeId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 PointCost = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> PrerequisiteNodeIds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESkillNodeRewardType RewardType = ESkillNodeRewardType::StatBonus;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCharacterStats StatBonus;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AbilityId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag WeaponProficiencyTag;
};
