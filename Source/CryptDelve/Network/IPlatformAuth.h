// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPlatformAuth.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAuthComplete, bool, bSuccess, const FString&, AccountId);

UINTERFACE(BlueprintType)
class UPlatformAuth : public UInterface
{
	GENERATED_BODY()
};

class CRYPTDELVE_API IPlatformAuth
{
	GENERATED_BODY()

public:
	virtual void Login() = 0;
	virtual void Logout() = 0;
	virtual bool IsLoggedIn() const = 0;
	virtual FString GetAccountId() const = 0;
};
