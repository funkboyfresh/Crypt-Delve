// Copyright CryptDelve. All Rights Reserved.

#include "Core/CryptDelvePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "Core/CryptDelveCharacter.h"
#include "UI/MainMenuWidget.h"
#include "UI/CharacterSelectWidget.h"
#include "UI/LobbyWidget.h"
#include "Abilities/CryptDelveAbilitySystemComponent.h"
#include "Core/TopDownCameraManager.h"

ACryptDelvePlayerController::ACryptDelvePlayerController()
{
	bShowMouseCursor = false;
	PlayerCameraManagerClass = ATopDownCameraManager::StaticClass();
}

void ACryptDelvePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACryptDelvePlayerController::HandleMove);
		}
		if (LookAction)
		{
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACryptDelvePlayerController::HandleLook);
		}
		if (PrimaryAbilityAction)
		{
			EnhancedInput->BindAction(PrimaryAbilityAction, ETriggerEvent::Started, this, &ACryptDelvePlayerController::HandlePrimaryAbility);
		}
		if (SecondaryAbilityAction)
		{
			EnhancedInput->BindAction(SecondaryAbilityAction, ETriggerEvent::Started, this, &ACryptDelvePlayerController::HandleSecondaryAbility);
		}
	}
}

void ACryptDelvePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACryptDelvePlayerController::ShowMainMenu()
{
	if (!MainMenuWidgetClass)
	{
		return;
	}

	if (!MainMenuWidget)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetClass);
	}
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport(0);
	}
}

void ACryptDelvePlayerController::ShowCharacterSelect()
{
	if (!CharacterSelectWidgetClass)
	{
		return;
	}

	if (!CharacterSelectWidget)
	{
		CharacterSelectWidget = CreateWidget<UCharacterSelectWidget>(this, CharacterSelectWidgetClass);
	}
	if (CharacterSelectWidget)
	{
		CharacterSelectWidget->AddToViewport(0);
	}
}

void ACryptDelvePlayerController::ShowLobby()
{
	if (!LobbyWidgetClass)
	{
		return;
	}

	if (!LobbyWidget)
	{
		LobbyWidget = CreateWidget<ULobbyWidget>(this, LobbyWidgetClass);
	}
	if (LobbyWidget)
	{
		LobbyWidget->AddToViewport(0);
	}
}

void ACryptDelvePlayerController::HandleMove(const FInputActionValue& Value)
{
	if (ACryptDelveCharacter* Character = Cast<ACryptDelveCharacter>(GetPawn()))
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		Character->MoveTwinStick(MovementVector);
	}
}

void ACryptDelvePlayerController::HandleLook(const FInputActionValue& Value)
{
	if (ACryptDelveCharacter* Character = Cast<ACryptDelveCharacter>(GetPawn()))
	{
		const FVector2D LookVector = Value.Get<FVector2D>();
		if (!LookVector.IsNearlyZero())
		{
			const FRotator NewRotation(0.f, FMath::RadiansToDegrees(FMath::Atan2(LookVector.Y, LookVector.X)), 0.f);
			Character->SetActorRotation(NewRotation);
		}
	}
}

void ACryptDelvePlayerController::HandlePrimaryAbility()
{
	if (ACryptDelveCharacter* Character = Cast<ACryptDelveCharacter>(GetPawn()))
	{
		if (UCryptDelveAbilitySystemComponent* ASC = Character->GetCryptDelveAbilitySystemComponent())
		{
			ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(FGameplayTag::RequestGameplayTag(FName("Ability.Primary"))));
		}
	}
}

void ACryptDelvePlayerController::HandleSecondaryAbility()
{
	if (ACryptDelveCharacter* Character = Cast<ACryptDelveCharacter>(GetPawn()))
	{
		if (UCryptDelveAbilitySystemComponent* ASC = Character->GetCryptDelveAbilitySystemComponent())
		{
			ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(FGameplayTag::RequestGameplayTag(FName("Ability.Secondary"))));
		}
	}
}
