// Copyright CryptDelve. All Rights Reserved.

#include "Characters/StatCalculator.h"
#include "Equipment/ItemDefinition.h"
#include "Progression/SkillTreeTypes.h"
#include "Roguelike/RunModifierTypes.h"

FAggregatedStats UStatCalculator::CalculateStats(const FCharacterProfile& Profile,
	const TMap<EEquipmentSlot, UItemDefinition*>& EquippedDefinitions,
	const TArray<FRunModifier>& RunModifiers,
	const TArray<FSkillTreeNode>& UnlockedNodes)
{
	FAggregatedStats Stats;
	Stats.Attributes = Profile.BaseStats;

	for (const FSkillTreeNode& Node : UnlockedNodes)
	{
		Stats.Attributes.Strength += Node.StatBonus.Strength;
		Stats.Attributes.Dexterity += Node.StatBonus.Dexterity;
		Stats.Attributes.Constitution += Node.StatBonus.Constitution;
		Stats.Attributes.Intelligence += Node.StatBonus.Intelligence;
		Stats.Attributes.Wisdom += Node.StatBonus.Wisdom;
		Stats.Attributes.Charisma += Node.StatBonus.Charisma;
	}

	for (const TPair<EEquipmentSlot, UItemDefinition*>& Pair : EquippedDefinitions)
	{
		if (const UItemDefinition* Item = Pair.Value)
		{
			Stats.Armor += Item->ArmorBonus;
			Stats.Evasion += Item->EvasionBonus;
			Stats.BaseDamage += Item->BaseDamage;
		}
	}

	Stats.MaxHealth = 50.f + Stats.Attributes.Constitution * 5.f;
	Stats.MaxMana = 20.f + Stats.Attributes.Intelligence * 3.f + Stats.Attributes.Wisdom * 2.f;
	Stats.DamageMultiplier = 1.f + Stats.Attributes.Strength * 0.02f;

	for (const FRunModifier& Modifier : RunModifiers)
	{
		if (Modifier.Type == ERunModifierType::DamageBonus)
		{
			Stats.DamageMultiplier += Modifier.Magnitude;
		}
	}

	return Stats;
}
