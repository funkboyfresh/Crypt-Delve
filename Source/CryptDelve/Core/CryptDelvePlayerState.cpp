// Copyright CryptDelve. All Rights Reserved.

#include "Core/CryptDelvePlayerState.h"
#include "Net/UnrealNetwork.h"

ACryptDelvePlayerState::ACryptDelvePlayerState()
{
	bReplicates = true;
}

void ACryptDelvePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ACryptDelvePlayerState, CharacterProfile);
}

void ACryptDelvePlayerState::SetCharacterProfile(const FCharacterProfile& Profile)
{
	if (HasAuthority())
	{
		CharacterProfile = Profile;
	}
}

void ACryptDelvePlayerState::OnRep_CharacterProfile()
{
}
