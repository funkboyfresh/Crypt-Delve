// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Characters/CharacterProfileTypes.h"
#include "CharacterSelectWidget.generated.h"

UCLASS(Abstract, Blueprintable)
class CRYPTDELVE_API UCharacterSelectWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateCharacter(const FString& Name, ECryptRace Race, ECryptClass Class);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SelectCharacter(const FCharacterProfile& Profile);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ContinueToLobby();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TArray<FCharacterProfile> AvailableProfiles;
};
