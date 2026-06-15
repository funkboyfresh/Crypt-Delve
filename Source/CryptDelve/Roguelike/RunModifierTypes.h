// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Roguelike/RunModifierTypes.generated.h"

UENUM(BlueprintType)
enum class ERunModifierType : uint8
{
	DamageBonus,
	ResourceBonus,
	DropRateBonus,
	HazardDensity,
	EliteDensity
};

USTRUCT(BlueprintType)
struct FRunModifier
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERunModifierType Type = ERunModifierType::DamageBonus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Magnitude = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SourceDescription;
};

UENUM(BlueprintType)
enum class ERunPhase : uint8
{
	NotStarted,
	InProgress,
	FloorComplete,
	BossActive,
	RunComplete,
	PartyWiped
};
