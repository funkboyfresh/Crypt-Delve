// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Characters/CharacterProfileTypes.h"
#include "PlayFabPersistenceService.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProfilesLoaded, bool, bSuccess, const TArray<FCharacterProfile>&, Profiles);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProfileSaved, bool, bSuccess);

UCLASS(BlueprintType)
class CRYPTDELVE_API UPlayFabPersistenceService : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PlayFab")
	void LoadCharacterProfiles(const FString& AccountId);

	UFUNCTION(BlueprintCallable, Category = "PlayFab")
	void SaveCharacterProfile(const FCharacterProfile& Profile);

	UFUNCTION(BlueprintCallable, Category = "PlayFab")
	void SaveCheckpointProfiles(const TArray<FCharacterProfile>& Profiles);

	UPROPERTY(BlueprintAssignable, Category = "PlayFab")
	FOnProfilesLoaded OnProfilesLoaded;

	UPROPERTY(BlueprintAssignable, Category = "PlayFab")
	FOnProfileSaved OnProfileSaved;

protected:
	FString GetTitleId() const;
	FString GetSecretKey() const;
	void SaveProfilesLocally(const TArray<FCharacterProfile>& Profiles) const;
	bool LoadProfilesLocally(const FString& AccountId, TArray<FCharacterProfile>& OutProfiles) const;
	FString GetLocalSavePath(const FString& AccountId) const;
};
