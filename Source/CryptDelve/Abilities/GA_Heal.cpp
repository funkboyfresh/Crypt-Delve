// Copyright CryptDelve. All Rights Reserved.

#include "Abilities/GA_Heal.h"
#include "Abilities/CryptDelveAttributeSet.h"
#include "Core/CryptDelveCharacter.h"

UGA_Heal::UGA_Heal()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
}

void UGA_Heal::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
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

	TArray<AActor*> OverlappingActors;
	FCollisionShape Shape = FCollisionShape::MakeSphere(HealRadius);
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Heal), false, Avatar);
	FCollisionObjectQueryParams ObjectParams(ECC_Pawn);

	TArray<FOverlapResult> Overlaps;
	if (Avatar->GetWorld()->OverlapMultiByObjectType(Overlaps, Avatar->GetActorLocation(), FQuat::Identity, ObjectParams, Shape, Params))
	{
		for (const FOverlapResult& Overlap : Overlaps)
		{
			if (ACryptDelveCharacter* Ally = Cast<ACryptDelveCharacter>(Overlap.GetActor()))
			{
				if (UCryptDelveAttributeSet* AllyAttributes = const_cast<UCryptDelveAttributeSet*>(Ally->GetAbilitySystemComponent()->GetSet<UCryptDelveAttributeSet>()))
				{
					AllyAttributes->SetHealth(FMath::Min(AllyAttributes->GetHealth() + HealAmount, AllyAttributes->GetMaxHealth()));
				}
			}
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
