// Copyright CryptDelve. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CryptDelvePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class CRYPTDELVE_API ACryptDelvePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACryptDelvePlayerController();

	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowMainMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowCharacterSelect();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowLobby();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> PrimaryAbilityAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SecondaryAbilityAction;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCharacterSelectWidget> CharacterSelectWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class ULobbyWidget> LobbyWidgetClass;

	UPROPERTY()
	TObjectPtr<class UMainMenuWidget> MainMenuWidget;

	UPROPERTY()
	TObjectPtr<class UCharacterSelectWidget> CharacterSelectWidget;

	UPROPERTY()
	TObjectPtr<class ULobbyWidget> LobbyWidget;

	void HandleMove(const struct FInputActionValue& Value);
	void HandleLook(const struct FInputActionValue& Value);
	void HandlePrimaryAbility();
	void HandleSecondaryAbility();
};
