// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Characters/CharacterProfileTypes.h"
#include "ClassDefinition.generated.h"

UCLASS(BlueprintType)
class CRYPTDELVE_API UClassDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECryptClass CharacterClass = ECryptClass::Fighter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCharacterStats StartingStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer AllowedWeaponTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName SkillTreeId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> StartingItemIds;
};
