// Copyright CryptDelve. All Rights Reserved.

#include "Abilities/CryptDelveAttributeSet.h"
#include "Net/UnrealNetwork.h"

UCryptDelveAttributeSet::UCryptDelveAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(50.f);
	InitArmor(0.f);
	InitBaseDamage(10.f);
	InitDamageMultiplier(1.f);
}

void UCryptDelveAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCryptDelveAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCryptDelveAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCryptDelveAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCryptDelveAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCryptDelveAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCryptDelveAttributeSet, BaseDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCryptDelveAttributeSet, DamageMultiplier, COND_None, REPNOTIFY_Always);
}

void UCryptDelveAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UCryptDelveAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) { GAMEPLAYATTRIBUTE_REPNOTIFY(UCryptDelveAttributeSet, Health, OldHealth); }
void UCryptDelveAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) { GAMEPLAYATTRIBUTE_REPNOTIFY(UCryptDelveAttributeSet, MaxHealth, OldMaxHealth); }
void UCryptDelveAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) { GAMEPLAYATTRIBUTE_REPNOTIFY(UCryptDelveAttributeSet, Mana, OldMana); }
void UCryptDelveAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) { GAMEPLAYATTRIBUTE_REPNOTIFY(UCryptDelveAttributeSet, MaxMana, OldMaxMana); }
void UCryptDelveAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) { GAMEPLAYATTRIBUTE_REPNOTIFY(UCryptDelveAttributeSet, Armor, OldArmor); }
void UCryptDelveAttributeSet::OnRep_BaseDamage(const FGameplayAttributeData& OldBaseDamage) { GAMEPLAYATTRIBUTE_REPNOTIFY(UCryptDelveAttributeSet, BaseDamage, OldBaseDamage); }
void UCryptDelveAttributeSet::OnRep_DamageMultiplier(const FGameplayAttributeData& OldDamageMultiplier) { GAMEPLAYATTRIBUTE_REPNOTIFY(UCryptDelveAttributeSet, DamageMultiplier, OldDamageMultiplier); }
