// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelGen/LevelGenTypes.h"
#include "LevelGenSubsystem.generated.h"

UCLASS()
class CRYPTDELVE_API ULevelGenSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "LevelGen")
	FGeneratedFloor GenerateZoneFloor(FName ZoneId, int32 FloorIndex, int32 Seed) const;
};
