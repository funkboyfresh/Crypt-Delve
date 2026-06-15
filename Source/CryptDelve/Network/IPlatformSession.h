// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPlatformSession.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionReady, const FString&, SessionId);

UINTERFACE(BlueprintType)
class UPlatformSession : public UInterface
{
	GENERATED_BODY()
};

class CRYPTDELVE_API IPlatformSession
{
	GENERATED_BODY()

public:
	virtual void CreateSession(int32 MaxPlayers) = 0;
	virtual void FindSessions() = 0;
	virtual void JoinSession(const FString& SessionId) = 0;
	virtual void DestroySession() = 0;
};
