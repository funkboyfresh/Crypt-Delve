// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CryptDelveGameMode.generated.h"

UCLASS()
class CRYPTDELVE_API ACryptDelveGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACryptDelveGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UFUNCTION(BlueprintCallable, Category = "Run")
	void BeginRun(FName ZoneId, int32 Seed);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Run")
	FName DefaultZoneId = TEXT("CryptOfAsh");

	FTimerHandle DisconnectCheckpointTimer;
	void SaveCheckpointOnDisconnect();
};
