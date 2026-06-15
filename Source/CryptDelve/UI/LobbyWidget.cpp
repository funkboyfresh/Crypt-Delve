// Copyright CryptDelve. All Rights Reserved.

#include "UI/LobbyWidget.h"
#include "Core/CryptDelveGameInstance.h"
#include "Network/CryptDelveNetworkSubsystem.h"
#include "Network/EOSSessionService.h"
#include "Kismet/GameplayStatics.h"

void ULobbyWidget::HostRun()
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UCryptDelveNetworkSubsystem* Net = GI->GetSubsystem<UCryptDelveNetworkSubsystem>())
		{
			Net->CreateLobby(4);
			if (UEOSSessionService* Session = Net->GetSessionService())
			{
				CurrentSessionId = Session->GetCurrentSessionId();
			}
		}
	}
}

void ULobbyWidget::JoinRun(const FString& SessionId)
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UCryptDelveNetworkSubsystem* Net = GI->GetSubsystem<UCryptDelveNetworkSubsystem>())
		{
			Net->JoinLobby(SessionId);
			CurrentSessionId = SessionId;
		}
	}
}

void ULobbyWidget::StartRun()
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UCryptDelveGameInstance* CDGI = Cast<UCryptDelveGameInstance>(GI))
		{
			CDGI->SetFlowState(ECryptDelveFlowState::InRun);
			CDGI->TravelToMap(FName(TEXT("Zone01_Prototype")));
		}
	}
}
