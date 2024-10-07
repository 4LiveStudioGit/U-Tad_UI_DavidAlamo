// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* TryAgainButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitButton;

	void Show();


private:

	UFUNCTION()
	void TryAgain();
	UFUNCTION()
	void Quit();
};
