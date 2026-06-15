// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Equipment/EquipmentTypes.h"
#include "CryptDelveCharacter.generated.h"

class UCryptDelveAbilitySystemComponent;
class UCryptDelveAttributeSet;
class UCharacterProfileComponent;
class UEquipmentComponent;
class USkillTreeComponent;

UCLASS()
class CRYPTDELVE_API ACryptDelveCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACryptDelveCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Character")
	UCryptDelveAbilitySystemComponent* GetCryptDelveAbilitySystemComponent() const { return AbilitySystemComponent; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	UCharacterProfileComponent* GetProfileComponent() const { return ProfileComponent; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	UEquipmentComponent* GetEquipmentComponent() const { return EquipmentComponent; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	USkillTreeComponent* GetSkillTreeComponent() const { return SkillTreeComponent; }

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveTwinStick(const FVector2D& Input);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ApplyAggregatedStats(const FAggregatedStats& Stats);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UCryptDelveAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UCryptDelveAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<UCharacterProfileComponent> ProfileComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<UEquipmentComponent> EquipmentComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	TObjectPtr<USkillTreeComponent> SkillTreeComponent;

	UPROPERTY(Replicated)
	FVector ReplicatedMoveInput;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MoveSpeed = 600.f;

	void InitializeAbilityActorInfo();
	void GrantClassAbilities();
};
