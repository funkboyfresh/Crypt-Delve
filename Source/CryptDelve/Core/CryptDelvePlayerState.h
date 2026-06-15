// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Characters/CharacterProfileTypes.h"
#include "CryptDelvePlayerState.generated.h"

UCLASS()
class CRYPTDELVE_API ACryptDelvePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ACryptDelvePlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetCharacterProfile(const FCharacterProfile& Profile);

	UFUNCTION(BlueprintPure, Category = "Character")
	const FCharacterProfile& GetCharacterProfile() const { return CharacterProfile; }

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CharacterProfile, BlueprintReadOnly, Category = "Character")
	FCharacterProfile CharacterProfile;

	UFUNCTION()
	void OnRep_CharacterProfile();
};
