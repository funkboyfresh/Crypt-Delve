// Copyright CryptDelve. All Rights Reserved.

#include "Core/CryptDelveCharacter.h"
#include "Abilities/CryptDelveAbilitySystemComponent.h"
#include "Abilities/CryptDelveAttributeSet.h"
#include "Abilities/GA_MeleeAttack.h"
#include "Abilities/GA_Fireball.h"
#include "Abilities/GA_Heal.h"
#include "Characters/CharacterProfileComponent.h"
#include "Equipment/EquipmentComponent.h"
#include "Progression/SkillTreeComponent.h"
#include "Core/CryptDelvePlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

ACryptDelveCharacter::ACryptDelveCharacter()
{
	bReplicates = true;
	SetReplicateMovement(true);

	AbilitySystemComponent = CreateDefaultSubobject<UCryptDelveAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UCryptDelveAttributeSet>(TEXT("AttributeSet"));
	ProfileComponent = CreateDefaultSubobject<UCharacterProfileComponent>(TEXT("ProfileComponent"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
	SkillTreeComponent = CreateDefaultSubobject<USkillTreeComponent>(TEXT("SkillTreeComponent"));

	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->bOrientRotationToMovement = true;
		Movement->RotationRate = FRotator(0.f, 720.f, 0.f);
		Movement->MaxWalkSpeed = MoveSpeed;
		Movement->bConstrainToPlane = true;
		Movement->SetPlaneConstraintNormal(FVector::UpVector);
	}
}

void ACryptDelveCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACryptDelveCharacter, ReplicatedMoveInput);
}

void ACryptDelveCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitializeAbilityActorInfo();
	GrantClassAbilities();
}

void ACryptDelveCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitializeAbilityActorInfo();
}

UAbilitySystemComponent* ACryptDelveCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACryptDelveCharacter::MoveTwinStick(const FVector2D& Input)
{
	if (Input.IsNearlyZero())
	{
		return;
	}

	const FRotator ControlRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector Direction = FRotationMatrix(ControlRotation).TransformVector(FVector(Input.X, Input.Y, 0.f));
	AddMovementInput(Direction.GetSafeNormal(), 1.f);

	if (HasAuthority())
	{
		ReplicatedMoveInput = Direction;
	}
}

void ACryptDelveCharacter::ApplyAggregatedStats(const FAggregatedStats& Stats)
{
	if (!AbilitySystemComponent || !AttributeSet)
	{
		return;
	}

	AttributeSet->SetMaxHealth(Stats.MaxHealth);
	AttributeSet->SetHealth(Stats.MaxHealth);
	AttributeSet->SetMaxMana(Stats.MaxMana);
	AttributeSet->SetMana(Stats.MaxMana);
	AttributeSet->SetArmor(Stats.Armor);
	AttributeSet->SetBaseDamage(Stats.BaseDamage);
	AttributeSet->SetDamageMultiplier(Stats.DamageMultiplier);
}

void ACryptDelveCharacter::InitializeAbilityActorInfo()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (HasAuthority() && ProfileComponent)
	{
		if (ACryptDelvePlayerState* PS = GetPlayerState<ACryptDelvePlayerState>())
		{
			ProfileComponent->SetProfile(PS->GetCharacterProfile());
		}
		EquipmentComponent->RefreshStats();
	}
}

void ACryptDelveCharacter::GrantClassAbilities()
{
	if (!HasAuthority() || !AbilitySystemComponent || !ProfileComponent)
	{
		return;
	}

	TArray<TSubclassOf<UGameplayAbility>> Abilities;
	switch (ProfileComponent->GetProfile().CharacterClass)
	{
	case ECryptClass::Fighter:
		Abilities.Add(UGA_MeleeAttack::StaticClass());
		break;
	case ECryptClass::Wizard:
		Abilities.Add(UGA_Fireball::StaticClass());
		break;
	case ECryptClass::Cleric:
		Abilities.Add(UGA_Heal::StaticClass());
		Abilities.Add(UGA_MeleeAttack::StaticClass());
		break;
	default:
		Abilities.Add(UGA_MeleeAttack::StaticClass());
		break;
	}

	AbilitySystemComponent->InitializeDefaultAbilities(Abilities);
}
