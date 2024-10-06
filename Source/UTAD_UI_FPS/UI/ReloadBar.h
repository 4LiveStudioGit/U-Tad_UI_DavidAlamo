// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReloadBar.generated.h"

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UReloadBar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Show();

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();

private:

	UFUNCTION(BlueprintCallable, Category="Reload")
	void UpdateReloadBarValue(float NewValue);

public:

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ReloadBar;
};
