// Copyright CryptDelve. All Rights Reserved.

#include "LevelGen/RoomGraphGenerator.h"

FGeneratedFloor FRoomGraphGenerator::GenerateFloor(int32 FloorIndex, int32 Seed, int32 RoomCount) const
{
	FGeneratedFloor Floor;
	Floor.FloorIndex = FloorIndex;
	Floor.RoomGraph = BuildRoomGraph(Seed, RoomCount, false);
	StampTiles(Floor);
	return Floor;
}

FGeneratedFloor FRoomGraphGenerator::GenerateBossFloor(int32 Seed, FName ZoneId) const
{
	FGeneratedFloor Floor;
	Floor.FloorIndex = 99;
	Floor.RoomGraph = BuildRoomGraph(Seed, 1, true);
	StampTiles(Floor);
	return Floor;
}

FRoomGraph FRoomGraphGenerator::BuildRoomGraph(int32 Seed, int32 RoomCount, bool bBossRoom) const
{
	FRoomGraph Graph;
	FRandomStream Stream(Seed);

	FIntPoint Cursor(0, 0);
	FGuid PreviousRoomId;

	for (int32 Index = 0; Index < RoomCount; ++Index)
	{
		FRoomNode Room;
		Room.RoomId = FGuid::NewGuid();
		Room.GridPosition = Cursor;
		Room.RoomSize = FIntPoint(Stream.RandRange(6, 10), Stream.RandRange(6, 10));
		Room.bIsBossRoom = bBossRoom;
		Room.bIsTreasureRoom = !bBossRoom && Stream.FRand() > 0.8f;

		Graph.Rooms.Add(Room);

		if (Index == 0)
		{
			Graph.StartRoomId = Room.RoomId;
		}
		if (Index == RoomCount - 1)
		{
			Graph.ExitRoomId = Room.RoomId;
		}

		if (PreviousRoomId.IsValid())
		{
			FRoomEdge Edge;
			Edge.FromRoomId = PreviousRoomId;
			Edge.ToRoomId = Room.RoomId;
			Graph.Edges.Add(Edge);
		}

		PreviousRoomId = Room.RoomId;
		Cursor.X += Stream.RandRange(8, 12);
		if (Stream.FRand() > 0.5f)
		{
			Cursor.Y += Stream.RandRange(-4, 4);
		}
	}

	return Graph;
}

void FRoomGraphGenerator::StampTiles(FGeneratedFloor& Floor) const
{
	FIntPoint Min(INT32_MAX, INT32_MAX);
	FIntPoint Max(INT32_MIN, INT32_MIN);

	for (const FRoomNode& Room : Floor.RoomGraph.Rooms)
	{
		Min.X = FMath::Min(Min.X, Room.GridPosition.X);
		Min.Y = FMath::Min(Min.Y, Room.GridPosition.Y);
		Max.X = FMath::Max(Max.X, Room.GridPosition.X + Room.RoomSize.X);
		Max.Y = FMath::Max(Max.Y, Room.GridPosition.Y + Room.RoomSize.Y);
	}

	const FIntPoint Dimensions = Max - Min + FIntPoint(2, 2);
	Floor.GridDimensions = Dimensions;
	Floor.TileGrid.Init(ETileType::Wall, Dimensions.X * Dimensions.Y);

	auto SetTile = [&](FIntPoint Pos, ETileType Type)
	{
		const FIntPoint Local = Pos - Min + FIntPoint(1, 1);
		if (Local.X >= 0 && Local.Y >= 0 && Local.X < Dimensions.X && Local.Y < Dimensions.Y)
		{
			Floor.TileGrid[Local.Y * Dimensions.X + Local.X] = Type;
		}
	};

	for (const FRoomNode& Room : Floor.RoomGraph.Rooms)
	{
		for (int32 Y = 0; Y < Room.RoomSize.Y; ++Y)
		{
			for (int32 X = 0; X < Room.RoomSize.X; ++X)
			{
				SetTile(Room.GridPosition + FIntPoint(X, Y), ETileType::Floor);
			}
		}

		SetTile(Room.GridPosition, Room.RoomId == Floor.RoomGraph.StartRoomId ? ETileType::Spawn : ETileType::Floor);
		if (Room.RoomId == Floor.RoomGraph.ExitRoomId)
		{
			SetTile(Room.GridPosition + FIntPoint(Room.RoomSize.X / 2, Room.RoomSize.Y / 2), ETileType::Exit);
		}
		if (Room.bIsTreasureRoom)
		{
			SetTile(Room.GridPosition + FIntPoint(1, 1), ETileType::Treasure);
		}
		if (Room.bIsBossRoom)
		{
			SetTile(Room.GridPosition + FIntPoint(Room.RoomSize.X / 2, Room.RoomSize.Y / 2), ETileType::Hazard);
		}
	}
}
