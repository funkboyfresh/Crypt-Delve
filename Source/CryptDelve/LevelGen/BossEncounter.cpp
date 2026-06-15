// Copyright CryptDelve. All Rights Reserved.

#include "LevelGen/BossEncounter.h"
#include "Roguelike/RunStateComponent.h"
#include "Core/CryptDelveGameState.h"
#include "Net/UnrealNetwork.h"

ABossEncounter::ABossEncounter()
{
	bReplicates = true;
}

void ABossEncounter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABossEncounter, bBossActive);
	DOREPLIFETIME(ABossEncounter, ActiveBossId);
}

void ABossEncounter::ActivateBoss(FName BossId)
{
	if (!HasAuthority())
	{
		return;
	}

	bBossActive = true;
	ActiveBossId = BossId;
}

void ABossEncounter::OnBossDefeated()
{
	if (!HasAuthority())
	{
		return;
	}

	bBossActive = false;
	BossDefeated.Broadcast();

	if (ACryptDelveGameState* GS = GetWorld()->GetGameState<ACryptDelveGameState>())
	{
		if (URunStateComponent* RunState = GS->GetRunStateComponent())
		{
			RunState->CompleteRun();
		}
	}
}

void ABossEncounter::OnRep_BossActive()
{
}
