// Copyright CryptDelve. All Rights Reserved.

#include "Abilities/GA_MeleeAttack.h"
#include "Abilities/CryptDelveAttributeSet.h"
#include "Core/CryptDelveCharacter.h"
#include "Kismet/GameplayStatics.h"

UGA_MeleeAttack::UGA_MeleeAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
}

void UGA_MeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
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

	const UCryptDelveAttributeSet* Attributes = ActorInfo->AbilitySystemComponent->GetSet<UCryptDelveAttributeSet>();
	const float Damage = Attributes ? Attributes->GetBaseDamage() * Attributes->GetDamageMultiplier() : 10.f;

	TArray<FHitResult> Hits;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(MeleeAttack), false, Avatar);
	const FVector Origin = Avatar->GetActorLocation();
	const FVector End = Origin + Avatar->GetActorForwardVector() * AttackRange;

	if (Avatar->GetWorld()->SweepMultiByChannel(Hits, Origin, End, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(AttackRadius), Params))
	{
		for (const FHitResult& Hit : Hits)
		{
			AActor* Target = Hit.GetActor();
			if (Target && Target != Avatar)
			{
				UGameplayStatics::ApplyDamage(Target, Damage, Avatar->GetInstigatorController(), Avatar, nullptr);
			}
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
