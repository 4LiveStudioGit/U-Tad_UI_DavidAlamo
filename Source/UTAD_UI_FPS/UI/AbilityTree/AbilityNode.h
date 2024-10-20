// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityNode.generated.h"

class UTextBlock;
class UProgressBar;
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

	virtual void NativeConstruct() override;
	
	

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

	//Texto para indicar el numero de puntos para desbloquear la habilidad
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PointsNeed;

	//Texto para indicar el numero de puntos para desbloquear la habilidad
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock_PointsNeed;

	//Texto para indicar que no has desbloqueado la habilidad anterior
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PreviousAbilityNeed;

	//Control de tiempo. Para desbloquear las habilidades en función del tiempo que presionas el botón

	// Tiempo necesario para desbloquear (en segundos).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill Tree")
	float RequiredHoldTime = 2.0f; 

	// Tiempo que el botón ha sido mantenido.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill Tree")
	float HoldTime = 0.0f; 

	
	FTimerHandle HoldTimerHandle;

	//Detecta incio de presionar el botón
	UFUNCTION(BlueprintCallable, Category="Skill Tree")
	void OnButtonPressed();

	//Detecta fin de presionar el botón
	UFUNCTION(BlueprintCallable, Category="Skill Tree")
	void OnButtonReleased();

	//Detecta el raton esta sobre el botón
	UFUNCTION(BlueprintCallable, Category="Skill Tree")
	void OnButtonHovered();

	//Detecta el raton no esta sobre el botón
	UFUNCTION(BlueprintCallable, Category="Skill Tree")
	void OnButtonUnhovered();
	
	//ProgressBar para mostrar el tiempo que se mantiene presionado el botón
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> TimeBar;

	
	
	//Puntos de coste para desbloquear la habilidad
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Node")
	int AbilityCost ;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr <UImage> ImageAbility;
	
	// Indica si el nodo está desbloqueado
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Node")
	bool bIsUnlocked = false; 

	//Imagen de la Habilidad
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Skill Node")
	FSlateBrush ImageNode;

private:

	
	TObjectPtr<AUTAD_UI_FPSCharacter> Player;

	bool Ability_Unlock;

	// Función interna para incrementar el tiempo
	void IncrementHoldTime();
	
;
};
