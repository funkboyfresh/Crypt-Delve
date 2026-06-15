// Copyright CryptDelve. All Rights Reserved.

#include "Roguelike/RunStateComponent.h"
#include "LevelGen/RoomGraphGenerator.h"
#include "Net/UnrealNetwork.h"

URunStateComponent::URunStateComponent()
{
	SetIsReplicatedByDefault(true);
}

void URunStateComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(URunStateComponent, RunSeed);
	DOREPLIFETIME(URunStateComponent, ZoneId);
	DOREPLIFETIME(URunStateComponent, CurrentFloor);
	DOREPLIFETIME(URunStateComponent, MaxFloorsBeforeBoss);
	DOREPLIFETIME(URunStateComponent, RunPhase);
	DOREPLIFETIME(URunStateComponent, ActiveModifiers);
	DOREPLIFETIME(URunStateComponent, CurrentFloorData);
}

void URunStateComponent::StartNewRun(int32 Seed, FName InZoneId)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	RunSeed = Seed > 0 ? Seed : FMath::Rand();
	ZoneId = InZoneId;
	CurrentFloor = 1;
	RunPhase = ERunPhase::InProgress;
	RollRunModifiers();

	FRoomGraphGenerator Generator;
	CurrentFloorData = Generator.GenerateFloor(CurrentFloor, RunSeed + CurrentFloor, 6);
	OnRunPhaseChanged.Broadcast(RunPhase);
}

void URunStateComponent::AdvanceFloor()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	if (CurrentFloor >= MaxFloorsBeforeBoss)
	{
		StartBossFight();
		return;
	}

	CurrentFloor++;
	RunPhase = ERunPhase::InProgress;

	FRoomGraphGenerator Generator;
	CurrentFloorData = Generator.GenerateFloor(CurrentFloor, RunSeed + CurrentFloor, 6);
	OnRunPhaseChanged.Broadcast(RunPhase);
}

void URunStateComponent::StartBossFight()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	RunPhase = ERunPhase::BossActive;
	FRoomGraphGenerator Generator;
	CurrentFloorData = Generator.GenerateBossFloor(RunSeed, ZoneId);
	OnRunPhaseChanged.Broadcast(RunPhase);
}

void URunStateComponent::CompleteRun()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	RunPhase = ERunPhase::RunComplete;
	OnRunPhaseChanged.Broadcast(RunPhase);
}

void URunStateComponent::MarkPartyWiped()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	RunPhase = ERunPhase::PartyWiped;
	OnRunPhaseChanged.Broadcast(RunPhase);
}

void URunStateComponent::RollRunModifiers()
{
	ActiveModifiers.Empty();
	FRandomStream Stream(RunSeed);

	if (Stream.FRand() > 0.5f)
	{
		FRunModifier Modifier;
		Modifier.Type = ERunModifierType::DamageBonus;
		Modifier.Magnitude = Stream.FRandRange(0.05f, 0.25f);
		Modifier.SourceDescription = TEXT("Empowered Foes");
		ActiveModifiers.Add(Modifier);
	}

	if (Stream.FRand() > 0.6f)
	{
		FRunModifier Modifier;
		Modifier.Type = ERunModifierType::DropRateBonus;
		Modifier.Magnitude = Stream.FRandRange(0.1f, 0.3f);
		Modifier.SourceDescription = TEXT("Plentiful Loot");
		ActiveModifiers.Add(Modifier);
	}
}
