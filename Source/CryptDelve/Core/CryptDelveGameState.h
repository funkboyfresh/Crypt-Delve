// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CryptDelveGameState.generated.h"

class URunStateComponent;

UCLASS()
class CRYPTDELVE_API ACryptDelveGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACryptDelveGameState();

	UFUNCTION(BlueprintCallable, Category = "Run")
	URunStateComponent* GetRunStateComponent() const { return RunStateComponent; }

	UFUNCTION(BlueprintCallable, Category = "Run")
	void StartZoneRun(FName ZoneId, int32 Seed);

	UFUNCTION(BlueprintCallable, Category = "Run")
	void CheckpointAllPlayers();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Run")
	TObjectPtr<URunStateComponent> RunStateComponent;
};
