// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterProfileTypes.h"
#include "EquipmentTypes.generated.h"

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	Helmet,
	Chest,
	Legs,
	Boots,
	Gloves,
	MainHand,
	OffHand,
	Accessory
};

USTRUCT(BlueprintType)
struct FItemInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid InstanceId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackCount = 1;
};

USTRUCT(BlueprintType)
struct FAggregatedStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMana = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Armor = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Evasion = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCharacterStats Attributes;
};
