// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMarker.generated.h"

class UBorder;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UPlayerMarker : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Hit;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* Border;
	

	void HitReact();
};
