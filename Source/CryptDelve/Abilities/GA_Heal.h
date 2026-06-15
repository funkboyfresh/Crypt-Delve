// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Heal.generated.h"

UCLASS()
class CRYPTDELVE_API UGA_Heal : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_Heal();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float ManaCost = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float HealAmount = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float HealRadius = 300.f;
};
