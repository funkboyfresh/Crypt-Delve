// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Progression/SkillTreeTypes.h"
#include "Progression/SkillTreeDefinition.h"
#include "SkillTreeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillUnlocked, FName, NodeId);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTDELVE_API USkillTreeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USkillTreeComponent();

	UFUNCTION(BlueprintCallable, Category = "Skills")
	bool CanUnlockNode(FName NodeId) const;

	UFUNCTION(BlueprintCallable, Category = "Skills")
	bool UnlockNode(FName NodeId);

	UFUNCTION(BlueprintCallable, Category = "Skills")
	TArray<FName> GetUnlockedNodeIds() const { return UnlockedNodeIds; }

	UFUNCTION(BlueprintCallable, Category = "Skills")
	void SetSkillTree(class USkillTreeDefinition* InTree) { SkillTree = InTree; }

	UFUNCTION(Server, Reliable, Category = "Skills")
	void Server_UnlockNode(FName NodeId);

	UPROPERTY(BlueprintAssignable, Category = "Skills")
	FOnSkillUnlocked OnSkillUnlocked;

protected:
	UPROPERTY()
	TObjectPtr<USkillTreeDefinition> SkillTree;

	UPROPERTY(ReplicatedUsing = OnRep_UnlockedNodes)
	TArray<FName> UnlockedNodeIds;

	UPROPERTY(Replicated)
	int32 AvailablePoints = 0;

	const FSkillTreeNode* FindNode(FName NodeId) const;
	bool HasPrerequisites(const FSkillTreeNode& Node) const;

	UFUNCTION()
	void OnRep_UnlockedNodes();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
