// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterProfileTypes.generated.h"

UENUM(BlueprintType)
enum class ECryptRace : uint8
{
	Human UMETA(DisplayName = "Human"),
	Elf UMETA(DisplayName = "Elf"),
	Dwarf UMETA(DisplayName = "Dwarf")
};

UENUM(BlueprintType)
enum class ECryptClass : uint8
{
	Fighter UMETA(DisplayName = "Fighter"),
	Wizard UMETA(DisplayName = "Wizard"),
	Cleric UMETA(DisplayName = "Cleric")
};

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strength = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Dexterity = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Constitution = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Intelligence = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Wisdom = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Charisma = 10.f;
};

USTRUCT(BlueprintType)
struct FInventoryEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackCount = 1;
};

USTRUCT(BlueprintType)
struct FCharacterProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid CharacterId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AccountId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECryptRace Race = ECryptRace::Human;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECryptClass CharacterClass = ECryptClass::Fighter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCharacterStats BaseStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Experience = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnspentSkillPoints = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> UnlockedSkillNodeIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FName> EquippedItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventoryEntry> Inventory;

	bool IsValid() const
	{
		return CharacterId.IsValid() && !CharacterName.IsEmpty();
	}
};
