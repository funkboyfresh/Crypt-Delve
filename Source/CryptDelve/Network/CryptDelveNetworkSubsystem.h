// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Characters/CharacterProfileTypes.h"
#include "CryptDelveNetworkSubsystem.generated.h"

class UEOSAuthService;
class UEOSSessionService;
class UPlayFabPersistenceService;

UCLASS()
class CRYPTDELVE_API UCryptDelveNetworkSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Network")
	UEOSAuthService* GetAuthService() const { return AuthService; }

	UFUNCTION(BlueprintCallable, Category = "Network")
	UEOSSessionService* GetSessionService() const { return SessionService; }

	UFUNCTION(BlueprintCallable, Category = "Network")
	UPlayFabPersistenceService* GetPersistenceService() const { return PersistenceService; }

	UFUNCTION(BlueprintCallable, Category = "Network")
	void Login();

	UFUNCTION(BlueprintCallable, Category = "Network")
	void CreateLobby(int32 MaxPlayers = 4);

	UFUNCTION(BlueprintCallable, Category = "Network")
	void JoinLobby(const FString& SessionId);

	UFUNCTION(BlueprintCallable, Category = "Network")
	void SaveSelectedCharacter(const FCharacterProfile& Profile);

	UFUNCTION(BlueprintCallable, Category = "Network")
	void LoadCharactersForAccount(const FString& AccountId);

	UFUNCTION(BlueprintPure, Category = "Network")
	const FCharacterProfile& GetSelectedCharacter() const { return SelectedCharacter; }

	UFUNCTION(BlueprintCallable, Category = "Network")
	void SetSelectedCharacter(const FCharacterProfile& Profile) { SelectedCharacter = Profile; }

protected:
	UPROPERTY()
	TObjectPtr<UEOSAuthService> AuthService;

	UPROPERTY()
	TObjectPtr<UEOSSessionService> SessionService;

	UPROPERTY()
	TObjectPtr<UPlayFabPersistenceService> PersistenceService;

	UPROPERTY()
	FCharacterProfile SelectedCharacter;

	UPROPERTY()
	TArray<FCharacterProfile> LoadedCharacters;

	UFUNCTION()
	void HandleAuthComplete(bool bSuccess, const FString& AccountId);

	UFUNCTION()
	void HandleProfilesLoaded(bool bSuccess, const TArray<FCharacterProfile>& Profiles);
};
