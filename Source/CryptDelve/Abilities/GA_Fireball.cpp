// Copyright CryptDelve. All Rights Reserved.

#include "Abilities/GA_Fireball.h"
#include "Abilities/CryptDelveAttributeSet.h"
#include "Kismet/GameplayStatics.h"

UGA_Fireball::UGA_Fireball()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
}

void UGA_Fireball::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AActor* Avatar = ActorInfo ? ActorInfo->AvatarActor.Get() : nullptr;
	if (!Avatar || !Avatar->HasAuthority())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	UCryptDelveAttributeSet* Attributes = const_cast<UCryptDelveAttributeSet*>(ActorInfo->AbilitySystemComponent->GetSet<UCryptDelveAttributeSet>());
	if (Attributes && Attributes->GetMana() < ManaCost)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (Attributes)
	{
		Attributes->SetMana(Attributes->GetMana() - ManaCost);
	}

	FHitResult Hit;
	const FVector Start = Avatar->GetActorLocation();
	const FVector End = Start + Avatar->GetActorForwardVector() * ProjectileRange;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Fireball), false, Avatar);

	if (Avatar->GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, Params))
	{
		if (AActor* Target = Hit.GetActor())
		{
			UGameplayStatics::ApplyDamage(Target, SpellDamage, Avatar->GetInstigatorController(), Avatar, nullptr);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
