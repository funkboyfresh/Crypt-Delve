// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LevelGen/LevelGenTypes.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	Floor,
	Wall,
	Hazard,
	Spawn,
	Exit,
	Treasure
};

USTRUCT(BlueprintType)
struct FRoomNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid RoomId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint GridPosition = FIntPoint::ZeroValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint RoomSize = FIntPoint(8, 8);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBossRoom = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsTreasureRoom = false;
};

USTRUCT(BlueprintType)
struct FRoomEdge
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid FromRoomId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid ToRoomId;
};

USTRUCT(BlueprintType)
struct FRoomGraph
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomNode> Rooms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomEdge> Edges;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid StartRoomId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid ExitRoomId;
};

USTRUCT(BlueprintType)
struct FGeneratedFloor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FloorIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRoomGraph RoomGraph;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ETileType> TileGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint GridDimensions = FIntPoint::ZeroValue;
};
