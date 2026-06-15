// Copyright CryptDelve. All Rights Reserved.

#include "Equipment/EquipmentComponent.h"
#include "Equipment/ItemDefinition.h"
#include "Characters/CharacterProfileComponent.h"
#include "Characters/StatCalculator.h"
#include "Core/CryptDelveCharacter.h"
#include "Net/UnrealNetwork.h"

UEquipmentComponent::UEquipmentComponent()
{
	SetIsReplicatedByDefault(true);
}

void UEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UEquipmentComponent, EquippedItems);
	DOREPLIFETIME(UEquipmentComponent, CachedStats);
}

bool UEquipmentComponent::EquipItem(EEquipmentSlot Slot, FName ItemId)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		UItemDefinition* ItemDef = Cast<UItemDefinition>(StaticLoadObject(UItemDefinition::StaticClass(), nullptr, *FString::Printf(TEXT("/Game/Data/Items/DA_%s.DA_%s"), *ItemId.ToString(), *ItemId.ToString())));
		if (!CanEquip(ItemDef))
		{
			return false;
		}
		EquippedItems.Add(Slot, ItemId);
		RefreshStats();
		OnEquipmentChanged.Broadcast();
		return true;
	}

	Server_EquipItem(Slot, ItemId);
	return true;
}

bool UEquipmentComponent::UnequipItem(EEquipmentSlot Slot)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return false;
	}

	EquippedItems.Remove(Slot);
	RefreshStats();
	OnEquipmentChanged.Broadcast();
	return true;
}

FName UEquipmentComponent::GetEquippedItemId(EEquipmentSlot Slot) const
{
	if (const FName* Found = EquippedItems.Find(Slot))
	{
		return *Found;
	}
	return NAME_None;
}

void UEquipmentComponent::RefreshStats()
{
	ACryptDelveCharacter* Character = Cast<ACryptDelveCharacter>(GetOwner());
	if (!Character)
	{
		return;
	}

	TMap<EEquipmentSlot, UItemDefinition*> Definitions;
	for (const TPair<EEquipmentSlot, FName>& Pair : EquippedItems)
	{
		if (UItemDefinition* Def = Cast<UItemDefinition>(StaticLoadObject(UItemDefinition::StaticClass(), nullptr,
			*FString::Printf(TEXT("/Game/Data/Items/DA_%s.DA_%s"), *Pair.Value.ToString(), *Pair.Value.ToString()))))
		{
			Definitions.Add(Pair.Key, Def);
		}
	}

	FCharacterProfile Profile;
	if (UCharacterProfileComponent* ProfileComp = Character->FindComponentByClass<UCharacterProfileComponent>())
	{
		Profile = ProfileComp->GetProfile();
	}

	CachedStats = UStatCalculator::CalculateStats(Profile, Definitions, {}, {});
	Character->ApplyAggregatedStats(CachedStats);
}

void UEquipmentComponent::Server_EquipItem_Implementation(EEquipmentSlot Slot, FName ItemId)
{
	EquipItem(Slot, ItemId);
}

void UEquipmentComponent::OnRep_EquippedItems()
{
	RefreshStats();
	OnEquipmentChanged.Broadcast();
}

bool UEquipmentComponent::CanEquip(UItemDefinition* ItemDef) const
{
	return ItemDef != nullptr;
}
