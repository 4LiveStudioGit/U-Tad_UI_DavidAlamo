// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityNode.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UAbilityNode : public UUserWidget
{
	GENERATED_BODY()
public:
	// Nombre de la habilidad
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Ability Node")
	FText NodeName;

	// Indica si el nodo está desbloqueado
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Node")
	bool bIsUnlocked = false; 

	//Imagen de la Habilidad
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Skill Node")
	FSlateBrush ImageNode;

	// Nodo anterior en la rama (nulo si es el primer nodo)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Node")
	UAbilityNode* PreviousNode;  

	// Verificar si el nodo se puede desbloquear
	UFUNCTION(BlueprintCallable, Category = "Skill Node")
	bool CanUnlock();  

	// Desbloquear el nodo
	UFUNCTION(BlueprintCallable, Category = "Skill Node")
	void Unlock();

	
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr <UImage> ImageAbility;
};
