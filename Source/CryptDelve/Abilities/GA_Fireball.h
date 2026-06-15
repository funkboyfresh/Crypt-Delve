// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Fireball.generated.h"

UCLASS()
class CRYPTDELVE_API UGA_Fireball : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_Fireball();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float ManaCost = 15.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float SpellDamage = 25.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float ProjectileRange = 800.f;
};
