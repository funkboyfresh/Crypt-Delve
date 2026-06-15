// Copyright CryptDelve. All Rights Reserved.

#include "Network/CryptDelveNetworkSubsystem.h"
#include "Network/EOSAuthService.h"
#include "Network/EOSSessionService.h"
#include "Network/PlayFabPersistenceService.h"

void UCryptDelveNetworkSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	AuthService = NewObject<UEOSAuthService>(this);
	SessionService = NewObject<UEOSSessionService>(this);
	PersistenceService = NewObject<UPlayFabPersistenceService>(this);

	AuthService->OnAuthComplete.AddDynamic(this, &UCryptDelveNetworkSubsystem::HandleAuthComplete);
	PersistenceService->OnProfilesLoaded.AddDynamic(this, &UCryptDelveNetworkSubsystem::HandleProfilesLoaded);
}

void UCryptDelveNetworkSubsystem::Login()
{
	if (AuthService)
	{
		AuthService->Login();
	}
}

void UCryptDelveNetworkSubsystem::CreateLobby(int32 MaxPlayers)
{
	if (SessionService)
	{
		SessionService->CreateSession(MaxPlayers);
	}
}

void UCryptDelveNetworkSubsystem::JoinLobby(const FString& SessionId)
{
	if (SessionService)
	{
		SessionService->JoinSession(SessionId);
	}
}

void UCryptDelveNetworkSubsystem::SaveSelectedCharacter(const FCharacterProfile& Profile)
{
	SelectedCharacter = Profile;
	if (PersistenceService)
	{
		PersistenceService->SaveCharacterProfile(Profile);
	}
}

void UCryptDelveNetworkSubsystem::LoadCharactersForAccount(const FString& AccountId)
{
	if (PersistenceService)
	{
		PersistenceService->LoadCharacterProfiles(AccountId);
	}
}

void UCryptDelveNetworkSubsystem::HandleAuthComplete(bool bSuccess, const FString& AccountId)
{
	if (bSuccess)
	{
		LoadCharactersForAccount(AccountId);
	}
}

void UCryptDelveNetworkSubsystem::HandleProfilesLoaded(bool bSuccess, const TArray<FCharacterProfile>& Profiles)
{
	LoadedCharacters = Profiles;
}
