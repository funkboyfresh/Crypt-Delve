// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/CharacterProfileTypes.h"
#include "CharacterProfileComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProfileChanged, const FCharacterProfile&, Profile);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTDELVE_API UCharacterProfileComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterProfileComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Character")
	const FCharacterProfile& GetProfile() const { return Profile; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetProfile(const FCharacterProfile& InProfile);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void InitializeNewProfile(const FString& AccountId, const FString& Name, ECryptRace Race, ECryptClass Class);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void AddExperience(int32 Amount);

	UFUNCTION(Server, Reliable, Category = "Character")
	void Server_SetProfile(const FCharacterProfile& InProfile);

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FOnProfileChanged OnProfileChanged;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_Profile, BlueprintReadOnly, Category = "Character")
	FCharacterProfile Profile;

	UFUNCTION()
	void OnRep_Profile();
};
