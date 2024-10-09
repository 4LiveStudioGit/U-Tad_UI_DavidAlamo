// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AblityTree.generated.h"

class UAbilityNode;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UAblityTree : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Tree")
	TArray<UAbilityNode*> SpeedBranch;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Tree")
	TArray<UAbilityNode*> HealthBranch;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skill Tree")
	TArray<UAbilityNode*> DamageBranch;

	UFUNCTION(BlueprintCallable, Category = "Skill Tree")
	void InitializeSkillTree();

	UFUNCTION(BlueprintCallable, Category = "Skill Tree")
	void UnlockSkillNode(UAbilityNode* SkillNode);
};
