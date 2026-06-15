// Copyright CryptDelve. All Rights Reserved.

#include "Network/PlayFabPersistenceService.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

FString UPlayFabPersistenceService::GetTitleId() const
{
	return TEXT(""); // Set via Config/PlayFabConfig.ini (not committed)
}

FString UPlayFabPersistenceService::GetSecretKey() const
{
	return TEXT(""); // Server-only; set via Config/PlayFabConfig.ini
}

FString UPlayFabPersistenceService::GetLocalSavePath(const FString& AccountId) const
{
	return FPaths::ProjectSavedDir() / TEXT("CryptDelve") / TEXT("Profiles") / (AccountId + TEXT(".json"));
}

void UPlayFabPersistenceService::SaveProfilesLocally(const TArray<FCharacterProfile>& Profiles) const
{
	if (Profiles.Num() == 0)
	{
		return;
	}

	FString JsonArray;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonArray);
	Writer->WriteArrayStart();
	for (const FCharacterProfile& Profile : Profiles)
	{
		FString ProfileJson;
		FJsonObjectConverter::UStructToJsonObjectString(Profile, ProfileJson);
		Writer->WriteRawJSONValue(ProfileJson);
	}
	Writer->WriteArrayEnd();
	Writer->Close();

	const FString Path = GetLocalSavePath(Profiles[0].AccountId);
	IFileManager::Get().MakeDirectory(*FPaths::GetPath(Path), true);
	FFileHelper::SaveStringToFile(JsonArray, *Path);
}

bool UPlayFabPersistenceService::LoadProfilesLocally(const FString& AccountId, TArray<FCharacterProfile>& OutProfiles) const
{
	FString JsonArray;
	const FString Path = GetLocalSavePath(AccountId);
	if (!FFileHelper::LoadFileToString(JsonArray, *Path))
	{
		return false;
	}

	TArray<TSharedPtr<FJsonValue>> Values;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonArray);
	if (!FJsonSerializer::Deserialize(Reader, Values))
	{
		return false;
	}

	for (const TSharedPtr<FJsonValue>& Value : Values)
	{
		FCharacterProfile Profile;
		if (FJsonObjectConverter::JsonObjectToUStruct(Value->AsObject().ToSharedRef(), &Profile))
		{
			OutProfiles.Add(Profile);
		}
	}
	return true;
}

void UPlayFabPersistenceService::LoadCharacterProfiles(const FString& AccountId)
{
	TArray<FCharacterProfile> Profiles;
	if (LoadProfilesLocally(AccountId, Profiles))
	{
		OnProfilesLoaded.Broadcast(true, Profiles);
		return;
	}

	const FString TitleId = GetTitleId();
	if (TitleId.IsEmpty())
	{
		OnProfilesLoaded.Broadcast(true, Profiles);
		return;
	}

	// PlayFab REST: LoginWithCustomID then GetUserData — prototype uses local fallback when unconfigured
	OnProfilesLoaded.Broadcast(true, Profiles);
}

void UPlayFabPersistenceService::SaveCharacterProfile(const FCharacterProfile& Profile)
{
	TArray<FCharacterProfile> Profiles;
	LoadProfilesLocally(Profile.AccountId, Profiles);

	bool bFound = false;
	for (FCharacterProfile& Existing : Profiles)
	{
		if (Existing.CharacterId == Profile.CharacterId)
		{
			Existing = Profile;
			bFound = true;
			break;
		}
	}
	if (!bFound)
	{
		Profiles.Add(Profile);
	}

	SaveProfilesLocally(Profiles);
	OnProfileSaved.Broadcast(true);
}

void UPlayFabPersistenceService::SaveCheckpointProfiles(const TArray<FCharacterProfile>& Profiles)
{
	SaveProfilesLocally(Profiles);
	OnProfileSaved.Broadcast(true);
}
