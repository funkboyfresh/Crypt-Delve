// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterProfileTypes.h"
#include "Equipment/EquipmentTypes.h"
#include "Roguelike/RunModifierTypes.h"
#include "Progression/SkillTreeTypes.h"
#include "StatCalculator.generated.h"

UCLASS()
class CRYPTDELVE_API UStatCalculator : public UObject
{
	GENERATED_BODY()

public:
	static FAggregatedStats CalculateStats(const FCharacterProfile& Profile,
		const TMap<EEquipmentSlot, class UItemDefinition*>& EquippedDefinitions,
		const TArray<FRunModifier>& RunModifiers,
		const TArray<FSkillTreeNode>& UnlockedNodes);
};
