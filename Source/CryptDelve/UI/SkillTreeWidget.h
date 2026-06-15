// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SkillTreeWidget.generated.h"

UCLASS(Abstract, Blueprintable)
class CRYPTDELVE_API USkillTreeWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RequestUnlockNode(FName NodeId);

protected:
	virtual void NativeConstruct() override;
};
