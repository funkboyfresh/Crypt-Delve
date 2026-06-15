// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Network/IPlatformSession.h"
#include "EOSSessionService.generated.h"

UCLASS(BlueprintType)
class CRYPTDELVE_API UEOSSessionService : public UObject, public IPlatformSession
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "EOS")
	FOnSessionReady OnSessionCreated;

	UPROPERTY(BlueprintAssignable, Category = "EOS")
	FOnSessionReady OnSessionJoined;

	virtual void CreateSession(int32 MaxPlayers) override;
	virtual void FindSessions() override;
	virtual void JoinSession(const FString& SessionId) override;
	virtual void DestroySession() override;

	UFUNCTION(BlueprintPure, Category = "EOS")
	FString GetCurrentSessionId() const { return CurrentSessionId; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "EOS")
	FString CurrentSessionId;

	int32 CachedMaxPlayers = 4;
};
