// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityNode.h"

bool UAbilityNode::CanUnlock()
{
	// El nodo puede desbloquearse si el nodo anterior está desbloqueado o si no hay nodo anterior (primer nodo)
	return PreviousNode == nullptr || PreviousNode->bIsUnlocked;
}


void UAbilityNode::Unlock()
{
}
