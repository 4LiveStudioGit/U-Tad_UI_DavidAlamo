// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair.generated.h"

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UCrosshair : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Show();

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Fire;

private:
	virtual void NativeConstruct() override;;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void playanim();
	bool WeaponDelegateBound = false;
};
