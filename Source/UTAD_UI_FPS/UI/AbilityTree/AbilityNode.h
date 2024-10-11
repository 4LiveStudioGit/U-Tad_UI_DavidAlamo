// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityNode.generated.h"

class AUTAD_UI_FPSCharacter;
class UImage;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UAbilityNode : public UUserWidget
{
	GENERATED_BODY()
public:
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

	//Boton para interactuar con el nodo
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ButtonActivateNode;

	//Boton para interactuar con el nodo
	UPROPERTY(BlueprintReadWrite)
	int AbilityCost ;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr <UImage> ImageAbility;
	
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
private:
	UFUNCTION()
	void onclick();
	
	TObjectPtr<AUTAD_UI_FPSCharacter> Player
;
};
