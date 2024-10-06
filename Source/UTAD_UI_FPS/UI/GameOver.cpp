// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOver::Show()
{
	APlayerController* PlayerController = GetOwningPlayer<APlayerController>();
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;
	PlayerController->Pause();
	TryAgainButton->SetFocus();
}

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();
	TryAgainButton->OnClicked.AddDynamic(this, &UGameOver::TryAgain);
	QuitButton->OnClicked.AddDynamic(this, &UGameOver::Quit);
}

void UGameOver::TryAgain()
{
	APlayerController* PlayerController = GetOwningPlayer<APlayerController>();
	PlayerController->RestartLevel();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
}

void UGameOver::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),NULL,EQuitPreference::Quit,true);
}
