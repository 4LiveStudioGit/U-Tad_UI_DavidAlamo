// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityNode.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

bool UAbilityNode::CanUnlock()
{
	// El nodo puede desbloquearse si el nodo anterior está desbloqueado o si no hay nodo anterior (primer nodo)
	return PreviousNode == nullptr || PreviousNode->bIsUnlocked;
}


void UAbilityNode::Unlock()
{
	if(CanUnlock())
	{
		Player->abilityPoints -= AbilityCost;
	}
}

void UAbilityNode::NativeConstruct()
{
	Super::NativeConstruct();
	ButtonActivateNode->OnClicked.AddDynamic(this, &UAbilityNode::onclick);
	
}

void UAbilityNode::NativePreConstruct()
{
	Super::NativePreConstruct();
	ImageNode.SetResourceObject(ImageAbility);
	ImageAbility->SetBrush(ImageNode);
	Player = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayer());
	
	
}

void UAbilityNode::onclick()
{
		if(Player)
		{
			if(Player->abilityPoints > AbilityCost)
			{
				Unlock();
			}
		}
	
}
