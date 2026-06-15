// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CryptDelveAbilitySystemComponent.generated.h"

UCLASS()
class CRYPTDELVE_API UCryptDelveAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void InitializeDefaultAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& Abilities);
};
