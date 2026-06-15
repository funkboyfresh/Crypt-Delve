// Copyright CryptDelve. All Rights Reserved.

#include "Core/CryptDelveGameState.h"
#include "Roguelike/RunStateComponent.h"
#include "Core/CryptDelvePlayerState.h"
#include "Network/CryptDelveNetworkSubsystem.h"
#include "Network/PlayFabPersistenceService.h"

ACryptDelveGameState::ACryptDelveGameState()
{
	RunStateComponent = CreateDefaultSubobject<URunStateComponent>(TEXT("RunStateComponent"));
}

void ACryptDelveGameState::StartZoneRun(FName ZoneId, int32 Seed)
{
	if (!HasAuthority() || !RunStateComponent)
	{
		return;
	}

	RunStateComponent->StartNewRun(Seed, ZoneId);
}

void ACryptDelveGameState::CheckpointAllPlayers()
{
	if (!HasAuthority())
	{
		return;
	}

	TArray<FCharacterProfile> Profiles;
	for (APlayerState* PS : PlayerArray)
	{
		if (ACryptDelvePlayerState* CDPS = Cast<ACryptDelvePlayerState>(PS))
		{
			Profiles.Add(CDPS->GetCharacterProfile());
		}
	}

	if (UGameInstance* GI = GetGameInstance())
	{
		if (UCryptDelveNetworkSubsystem* Net = GI->GetSubsystem<UCryptDelveNetworkSubsystem>())
		{
			if (UPlayFabPersistenceService* Persistence = Net->GetPersistenceService())
			{
				Persistence->SaveCheckpointProfiles(Profiles);
			}
		}
	}
}
