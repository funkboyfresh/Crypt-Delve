// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Characters/CharacterProfileTypes.h"
#include "RaceDefinition.generated.h"

UCLASS(BlueprintType)
class CRYPTDELVE_API URaceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECryptRace Race = ECryptRace::Human;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCharacterStats StatModifiers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName RacialSkillNodeId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ExperienceBonusPercent = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EvasionBonus = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ArmorBonus = 0.f;
};
