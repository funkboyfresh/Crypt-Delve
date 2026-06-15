// Copyright CryptDelve. All Rights Reserved.

#include "Characters/CharacterProfileComponent.h"
#include "Net/UnrealNetwork.h"

UCharacterProfileComponent::UCharacterProfileComponent()
{
	SetIsReplicatedByDefault(true);
}

void UCharacterProfileComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCharacterProfileComponent, Profile);
}

void UCharacterProfileComponent::SetProfile(const FCharacterProfile& InProfile)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		Profile = InProfile;
		OnProfileChanged.Broadcast(Profile);
	}
	else
	{
		Server_SetProfile(InProfile);
	}
}

void UCharacterProfileComponent::InitializeNewProfile(const FString& AccountId, const FString& Name, ECryptRace Race, ECryptClass Class)
{
	FCharacterProfile NewProfile;
	NewProfile.CharacterId = FGuid::NewGuid();
	NewProfile.AccountId = AccountId;
	NewProfile.CharacterName = Name;
	NewProfile.Race = Race;
	NewProfile.CharacterClass = Class;
	NewProfile.UnspentSkillPoints = 3;
	SetProfile(NewProfile);
}

void UCharacterProfileComponent::AddExperience(int32 Amount)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	Profile.Experience += Amount;
	while (Profile.Experience >= Profile.Level * 100)
	{
		Profile.Experience -= Profile.Level * 100;
		Profile.Level++;
		Profile.UnspentSkillPoints++;
	}
	OnProfileChanged.Broadcast(Profile);
}

void UCharacterProfileComponent::Server_SetProfile_Implementation(const FCharacterProfile& InProfile)
{
	SetProfile(InProfile);
}

void UCharacterProfileComponent::OnRep_Profile()
{
	OnProfileChanged.Broadcast(Profile);
}
