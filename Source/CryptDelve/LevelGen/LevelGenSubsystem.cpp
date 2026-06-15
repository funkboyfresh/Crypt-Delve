// Copyright CryptDelve. All Rights Reserved.

#include "LevelGen/LevelGenSubsystem.h"
#include "LevelGen/RoomGraphGenerator.h"

FGeneratedFloor ULevelGenSubsystem::GenerateZoneFloor(FName ZoneId, int32 FloorIndex, int32 Seed) const
{
	FRoomGraphGenerator Generator;
	return Generator.GenerateFloor(FloorIndex, Seed, 6);
}
