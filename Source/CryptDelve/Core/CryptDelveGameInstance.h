// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Characters/CharacterProfileTypes.h"
#include "CryptDelveGameInstance.generated.h"

UENUM(BlueprintType)
enum class ECryptDelveFlowState : uint8
{
	MainMenu,
	Login,
	CharacterSelect,
	Lobby,
	InRun
};

UCLASS()
class CRYPTDELVE_API UCryptDelveGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Flow")
	void SetFlowState(ECryptDelveFlowState NewState) { FlowState = NewState; }

	UFUNCTION(BlueprintPure, Category = "Flow")
	ECryptDelveFlowState GetFlowState() const { return FlowState; }

	UFUNCTION(BlueprintCallable, Category = "Flow")
	void TravelToMap(FName MapName);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Flow")
	ECryptDelveFlowState FlowState = ECryptDelveFlowState::MainMenu;
};
