// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "LobbyWidget.generated.h"

UCLASS(Abstract, Blueprintable)
class CRYPTDELVE_API ULobbyWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HostRun();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void JoinRun(const FString& SessionId);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void StartRun();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	FString CurrentSessionId;
};
