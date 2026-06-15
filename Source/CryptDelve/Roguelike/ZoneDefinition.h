// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ZoneDefinition.generated.h"

UCLASS(BlueprintType)
class CRYPTDELVE_API UZoneDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ZoneId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 FloorsBeforeBoss = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MinRooms = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxRooms = 8;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName BossEnemyId;
};
