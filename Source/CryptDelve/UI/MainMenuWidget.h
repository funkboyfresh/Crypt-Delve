// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MainMenuWidget.generated.h"

UCLASS(Abstract, Blueprintable)
class CRYPTDELVE_API UMainMenuWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnLoginClicked();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OnQuitClicked();

protected:
	virtual void NativeConstruct() override;
};
