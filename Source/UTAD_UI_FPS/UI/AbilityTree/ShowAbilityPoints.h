// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShowAbilityPoints.generated.h"

class AUTAD_UI_FPSCharacter;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UShowAbilityPoints : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "AbilityPoints")
	void UpdateAbilityPoints();

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	class UTextBlock* AbilityPoints;

	int32 puntos;

	AUTAD_UI_FPSCharacter* PlayerCharacter;



};
