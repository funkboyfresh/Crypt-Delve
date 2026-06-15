// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Network/IPlatformAuth.h"
#include "EOSAuthService.generated.h"

UCLASS(BlueprintType)
class CRYPTDELVE_API UEOSAuthService : public UObject, public IPlatformAuth
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "EOS")
	FOnAuthComplete OnAuthComplete;

	virtual void Login() override;
	virtual void Logout() override;
	virtual bool IsLoggedIn() const override { return bLoggedIn; }
	virtual FString GetAccountId() const override { return AccountId; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "EOS")
	bool bLoggedIn = false;

	UPROPERTY(BlueprintReadOnly, Category = "EOS")
	FString AccountId;

	void HandleLoginComplete(bool bSuccess, const FString& InAccountId);
};
