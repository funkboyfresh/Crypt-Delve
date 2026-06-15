// Copyright CryptDelve. All Rights Reserved.

#include "Abilities/CryptDelveAbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"

void UCryptDelveAbilitySystemComponent::InitializeDefaultAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	if (!IsOwnerActorAuthoritative())
	{
		return;
	}

	for (const TSubclassOf<UGameplayAbility>& AbilityClass : Abilities)
	{
		if (AbilityClass)
		{
			GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, INDEX_NONE, this));
		}
	}
}
