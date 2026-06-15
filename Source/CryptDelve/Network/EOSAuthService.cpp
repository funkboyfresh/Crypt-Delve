// Copyright CryptDelve. All Rights Reserved.

#include "Network/EOSAuthService.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"

void UEOSAuthService::Login()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem)
	{
		// Dev fallback when EOS is not configured
		AccountId = FGuid::NewGuid().ToString();
		bLoggedIn = true;
		HandleLoginComplete(true, AccountId);
		return;
	}

	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (!Identity.IsValid())
	{
		AccountId = FGuid::NewGuid().ToString();
		bLoggedIn = true;
		HandleLoginComplete(true, AccountId);
		return;
	}

	if (Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		AccountId = Identity->GetUniquePlayerId(0)->ToString();
		bLoggedIn = true;
		HandleLoginComplete(true, AccountId);
		return;
	}

	FOnlineAccountCredentials Credentials;
	Credentials.Type = TEXT("developer");
	Credentials.Id = TEXT("CryptDelveDev");
	Credentials.Token = TEXT("CryptDelveDevToken");

	Identity->OnLoginCompleteDelegates->AddLambda([this](int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
	{
		if (bWasSuccessful)
		{
			AccountId = UserId.ToString();
			bLoggedIn = true;
		}
		HandleLoginComplete(bWasSuccessful, AccountId);
	});

	Identity->Login(0, Credentials);
}

void UEOSAuthService::Logout()
{
	bLoggedIn = false;
	AccountId.Empty();
}

void UEOSAuthService::HandleLoginComplete(bool bSuccess, const FString& InAccountId)
{
	OnAuthComplete.Broadcast(bSuccess, InAccountId);
}
