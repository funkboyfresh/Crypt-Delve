// Copyright CryptDelve. All Rights Reserved.

#include "Network/EOSSessionService.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

void UEOSSessionService::CreateSession(int32 MaxPlayers)
{
	CachedMaxPlayers = MaxPlayers;
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem)
	{
		CurrentSessionId = FGuid::NewGuid().ToString();
		OnSessionCreated.Broadcast(CurrentSessionId);
		return;
	}

	IOnlineSessionPtr Sessions = Subsystem->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		CurrentSessionId = FGuid::NewGuid().ToString();
		OnSessionCreated.Broadcast(CurrentSessionId);
		return;
	}

	FOnlineSessionSettings Settings;
	Settings.NumPublicConnections = MaxPlayers;
	Settings.bShouldAdvertise = true;
	Settings.bAllowJoinInProgress = true;
	Settings.bIsLANMatch = false;
	CurrentSessionId = FGuid::NewGuid().ToString();
	Settings.Set(FName(TEXT("SESSION_ID")), CurrentSessionId, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	Sessions->OnCreateSessionCompleteDelegates.AddLambda([this](FName SessionName, bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			OnSessionCreated.Broadcast(CurrentSessionId);
		}
	});

	Sessions->CreateSession(0, FName(TEXT("CryptDelveSession")), Settings);
}

void UEOSSessionService::FindSessions()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem)
	{
		return;
	}

	IOnlineSessionPtr Sessions = Subsystem->GetSessionInterface();
	if (!Sessions.IsValid())
	{
		return;
	}

	Sessions->OnFindSessionsCompleteDelegates.AddLambda([](bool bWasSuccessful) {});
	Sessions->FindSessions(0, MakeShareable(new FOnlineSessionSearch()));
}

void UEOSSessionService::JoinSession(const FString& SessionId)
{
	CurrentSessionId = SessionId;
	OnSessionJoined.Broadcast(SessionId);
}

void UEOSSessionService::DestroySession()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		if (IOnlineSessionPtr Sessions = Subsystem->GetSessionInterface())
		{
			Sessions->DestroySession(FName(TEXT("CryptDelveSession")));
		}
	}
	CurrentSessionId.Empty();
}
