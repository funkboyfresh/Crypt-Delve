// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LevelGen/LevelGenTypes.h"

class CRYPTDELVE_API FRoomGraphGenerator
{
public:
	FGeneratedFloor GenerateFloor(int32 FloorIndex, int32 Seed, int32 RoomCount) const;
	FGeneratedFloor GenerateBossFloor(int32 Seed, FName ZoneId) const;

private:
	FRoomGraph BuildRoomGraph(int32 Seed, int32 RoomCount, bool bBossRoom) const;
	void StampTiles(FGeneratedFloor& Floor) const;
};
