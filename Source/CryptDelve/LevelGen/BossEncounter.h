// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossEncounter.generated.h"

UCLASS()
class CRYPTDELVE_API ABossEncounter : public AActor
{
	GENERATED_BODY()

public:
	ABossEncounter();

	UFUNCTION(BlueprintCallable, Category = "Boss")
	void ActivateBoss(FName BossId);

	UFUNCTION(BlueprintCallable, Category = "Boss")
	void OnBossDefeated();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBossDefeated);
	UPROPERTY(BlueprintAssignable, Category = "Boss")
	FOnBossDefeated BossDefeated;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_BossActive)
	bool bBossActive = false;

	UPROPERTY(Replicated)
	FName ActiveBossId;

	UFUNCTION()
	void OnRep_BossActive();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
