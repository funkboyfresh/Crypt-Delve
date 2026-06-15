// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment/EquipmentTypes.h"
#include "EquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentChanged);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTDELVE_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEquipmentComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool EquipItem(EEquipmentSlot Slot, FName ItemId);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool UnequipItem(EEquipmentSlot Slot);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	FName GetEquippedItemId(EEquipmentSlot Slot) const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	TMap<EEquipmentSlot, FName> GetAllEquippedItems() const { return EquippedItems; }

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	FAggregatedStats GetAggregatedStats() const { return CachedStats; }

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void RefreshStats();

	UFUNCTION(Server, Reliable, Category = "Equipment")
	void Server_EquipItem(EEquipmentSlot Slot, FName ItemId);

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentChanged OnEquipmentChanged;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_EquippedItems)
	TMap<EEquipmentSlot, FName> EquippedItems;

	UPROPERTY(Replicated)
	FAggregatedStats CachedStats;

	UFUNCTION()
	void OnRep_EquippedItems();

	bool CanEquip(class UItemDefinition* ItemDef) const;
};
