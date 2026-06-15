// Copyright CryptDelve. All Rights Reserved.

#include "UI/CharacterSelectWidget.h"
#include "Core/CryptDelveGameInstance.h"
#include "Core/CryptDelvePlayerController.h"
#include "Network/CryptDelveNetworkSubsystem.h"
#include "Network/EOSAuthService.h"
#include "Characters/CharacterProfileComponent.h"

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UGameInstance* GI = GetGameInstance())
	{
		if (UCryptDelveNetworkSubsystem* Net = GI->GetSubsystem<UCryptDelveNetworkSubsystem>())
		{
			if (UEOSAuthService* Auth = Net->GetAuthService())
			{
				if (Auth->IsLoggedIn())
				{
					Net->LoadCharactersForAccount(Auth->GetAccountId());
				}
			}
		}
	}
}

void UCharacterSelectWidget::CreateCharacter(const FString& Name, ECryptRace Race, ECryptClass Class)
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UCryptDelveNetworkSubsystem* Net = GI->GetSubsystem<UCryptDelveNetworkSubsystem>())
		{
			FCharacterProfile Profile;
			Profile.CharacterId = FGuid::NewGuid();
			Profile.AccountId = Net->GetAuthService() ? Net->GetAuthService()->GetAccountId() : FGuid::NewGuid().ToString();
			Profile.CharacterName = Name;
			Profile.Race = Race;
			Profile.CharacterClass = Class;
			Profile.UnspentSkillPoints = 3;
			AvailableProfiles.Add(Profile);
			Net->SaveSelectedCharacter(Profile);
		}
	}
}

void UCharacterSelectWidget::SelectCharacter(const FCharacterProfile& Profile)
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UCryptDelveNetworkSubsystem* Net = GI->GetSubsystem<UCryptDelveNetworkSubsystem>())
		{
			Net->SetSelectedCharacter(Profile);
			Net->SaveSelectedCharacter(Profile);
		}
	}
}

void UCharacterSelectWidget::ContinueToLobby()
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UCryptDelveGameInstance* CDGI = Cast<UCryptDelveGameInstance>(GI))
		{
			CDGI->SetFlowState(ECryptDelveFlowState::Lobby);
		}
	}

	if (APlayerController* PC = GetOwningPlayer())
	{
		if (ACryptDelvePlayerController* CDPC = Cast<ACryptDelvePlayerController>(PC))
		{
			DeactivateWidget();
			CDPC->ShowLobby();
		}
	}
}
