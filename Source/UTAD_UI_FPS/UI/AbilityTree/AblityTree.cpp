// Fill out your copyright notice in the Description page of Project Settings.


#include "AblityTree.h"

#include "AbilityNode.h"

void UAblityTree::InitializeSkillTree()
{
}

void UAblityTree::UnlockSkillNode(UAbilityNode* SkillNode)
{
	SkillNode->Unlock();
}
