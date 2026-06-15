// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Roguelike/RunModifierTypes.h"
#include "LevelGen/LevelGenTypes.h"
#include "RunStateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRunPhaseChanged, ERunPhase, NewPhase);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTDELVE_API URunStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URunStateComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Run")
	void StartNewRun(int32 Seed, FName ZoneId);

	UFUNCTION(BlueprintCallable, Category = "Run")
	void AdvanceFloor();

	UFUNCTION(BlueprintCallable, Category = "Run")
	void StartBossFight();

	UFUNCTION(BlueprintCallable, Category = "Run")
	void CompleteRun();

	UFUNCTION(BlueprintCallable, Category = "Run")
	void MarkPartyWiped();

	UFUNCTION(BlueprintPure, Category = "Run")
	int32 GetRunSeed() const { return RunSeed; }

	UFUNCTION(BlueprintPure, Category = "Run")
	int32 GetCurrentFloor() const { return CurrentFloor; }

	UFUNCTION(BlueprintPure, Category = "Run")
	ERunPhase GetRunPhase() const { return RunPhase; }

	UFUNCTION(BlueprintPure, Category = "Run")
	const TArray<FRunModifier>& GetActiveModifiers() const { return ActiveModifiers; }

	UFUNCTION(BlueprintPure, Category = "Run")
	const FGeneratedFloor& GetCurrentFloorData() const { return CurrentFloorData; }

	UPROPERTY(BlueprintAssignable, Category = "Run")
	FOnRunPhaseChanged OnRunPhaseChanged;

protected:
	UPROPERTY(Replicated)
	int32 RunSeed = 0;

	UPROPERTY(Replicated)
	FName ZoneId;

	UPROPERTY(Replicated)
	int32 CurrentFloor = 0;

	UPROPERTY(Replicated)
	int32 MaxFloorsBeforeBoss = 3;

	UPROPERTY(Replicated)
	ERunPhase RunPhase = ERunPhase::NotStarted;

	UPROPERTY(Replicated)
	TArray<FRunModifier> ActiveModifiers;

	UPROPERTY(Replicated)
	FGeneratedFloor CurrentFloorData;

	void RollRunModifiers();
};
