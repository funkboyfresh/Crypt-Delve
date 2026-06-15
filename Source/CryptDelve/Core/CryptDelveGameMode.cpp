// Copyright CryptDelve. All Rights Reserved.

#include "Core/CryptDelveGameMode.h"
#include "Core/CryptDelveGameState.h"
#include "Core/CryptDelvePlayerController.h"
#include "Core/CryptDelvePlayerState.h"
#include "Core/CryptDelveCharacter.h"
#include "Network/CryptDelveNetworkSubsystem.h"

ACryptDelveGameMode::ACryptDelveGameMode()
{
	GameStateClass = ACryptDelveGameState::StaticClass();
	PlayerControllerClass = ACryptDelvePlayerController::StaticClass();
	PlayerStateClass = ACryptDelvePlayerState::StaticClass();
	DefaultPawnClass = ACryptDelveCharacter::StaticClass();
	MaxPlayers = 4;
	bUseSeamlessTravel = true;
}

void ACryptDelveGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (ACryptDelvePlayerState* PS = NewPlayer->GetPlayerState<ACryptDelvePlayerState>())
	{
		if (UGameInstance* GI = GetGameInstance())
		{
			if (UCryptDelveNetworkSubsystem* Net = GI->GetSubsystem<UCryptDelveNetworkSubsystem>())
			{
				const FCharacterProfile& Selected = Net->GetSelectedCharacter();
				if (Selected.IsValid())
				{
					PS->SetCharacterProfile(Selected);
				}
			}
		}
	}
}

void ACryptDelveGameMode::Logout(AController* Exiting)
{
	GetWorldTimerManager().SetTimer(DisconnectCheckpointTimer, this, &ACryptDelveGameMode::SaveCheckpointOnDisconnect, 2.f, false);
	Super::Logout(Exiting);
}

void ACryptDelveGameMode::SaveCheckpointOnDisconnect()
{
	if (ACryptDelveGameState* GS = GetGameState<ACryptDelveGameState>())
	{
		GS->CheckpointAllPlayers();
	}
}

void ACryptDelveGameMode::BeginRun(FName ZoneId, int32 Seed)
{
	if (ACryptDelveGameState* GS = GetGameState<ACryptDelveGameState>())
	{
		GS->StartZoneRun(ZoneId.IsNone() ? DefaultZoneId : ZoneId, Seed);
	}
}
