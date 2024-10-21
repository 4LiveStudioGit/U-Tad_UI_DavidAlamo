// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityNode.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnitConversion.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

void UAbilityNode::NativeConstruct()
{
	Super::NativeConstruct();
	if (TimeBar)
	{
		TimeBar->SetVisibility(ESlateVisibility::Collapsed);
		TimeBar->SetPercent(0.0f);
	}
	if (ImageAbility)
	{
		ImageNode.SetResourceObject(ImageAbility);
		ImageAbility->SetBrush(ImageNode);
		PointsNeed->SetVisibility(ESlateVisibility::Collapsed);
		TextBlock_PointsNeed->SetVisibility(ESlateVisibility::Collapsed);
		PreviousAbilityNeed->SetVisibility(ESlateVisibility::Collapsed);
		
	}
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Player = Cast<AUTAD_UI_FPSCharacter>(PlayerController->GetPawn());

	if (ButtonActivateNode)
	{
		ButtonActivateNode->OnPressed.AddDynamic(this, &UAbilityNode::OnButtonPressed);
		ButtonActivateNode->OnReleased.AddDynamic(this, &UAbilityNode::OnButtonReleased);
		ButtonActivateNode->OnHovered.AddDynamic(this, &UAbilityNode::OnButtonHovered);
		ButtonActivateNode->OnUnhovered.AddDynamic(this, &UAbilityNode::OnButtonUnhovered);
		/*ButtonActivateNode->OnPressed.AddDynamic(this, &UAbilityNode::OnButtonPressed);
		ButtonActivateNode->OnPressed.AddDynamic(this, &UAbilityNode::OnButtonPressed);
		*/
	}

	
}

bool UAbilityNode::CanUnlock()
{
	if(Ability_Unlock)
	{
		return false;
	}
	// El nodo puede desbloquearse si el nodo anterior está desbloqueado o si no hay nodo anterior (primer nodo)
	return PreviousNode == nullptr || PreviousNode->bIsUnlocked;
}


void UAbilityNode::Unlock()
{
	if (CanUnlock())
	{
		if (Player->SetAbilityPoints(AbilityCost))
		{
			bIsUnlocked = true;
		}
	}
}



void UAbilityNode::OnButtonPressed()
{
	if(!bIsUnlocked)
	{
		if (CanUnlock())
		{
			GetWorld()->GetTimerManager().SetTimer(HoldTimerHandle, this, &UAbilityNode::IncrementHoldTime, 0.1, true);
		}
	}
}

void UAbilityNode::OnButtonReleased()
{
	if(!bIsUnlocked)
	{
		if (HoldTime >= RequiredHoldTime)
		{
			Unlock();
		}
		HoldTime = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(HoldTimerHandle);

		if (TimeBar)
		{
			TimeBar->SetVisibility(ESlateVisibility::Collapsed);
			TimeBar->SetPercent(0.0f);
		}
		
	}
}

void UAbilityNode::OnButtonHovered()
{

	if(!bIsUnlocked)
	{
		
		ButtonActivateNode->SetRenderScale(FVector2d(1.2, 1.2));
		if(PreviousNode && !PreviousNode->bIsUnlocked)
		{
			ImageAbility->SetBrushTintColor(FColor(0,0,0,128));
			PreviousAbilityNeed->SetVisibility(ESlateVisibility::Visible);
		}
		
		else if(Player->GetAbilityPoints() < AbilityCost)
		{
			
			ImageAbility->SetBrushTintColor(FColor(0,0,0,128));
			PointsNeed->SetVisibility(ESlateVisibility::HitTestInvisible);
			TextBlock_PointsNeed->SetVisibility(ESlateVisibility::HitTestInvisible);
			PointsNeed->SetText(FText::FromString(FString::FromInt(AbilityCost)));
		}
	}
}

void UAbilityNode::OnButtonUnhovered()
{
	ButtonActivateNode->SetRenderScale(FVector2d(1, 1));
	ImageAbility->SetBrushTintColor(FColor::White);
	PointsNeed->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_PointsNeed->SetVisibility(ESlateVisibility::Collapsed);
	PreviousAbilityNeed->SetVisibility(ESlateVisibility::Collapsed);
}

void UAbilityNode::IncrementHoldTime()
{
	HoldTime += 0.1;
	if(TimeBar)
	{
		TimeBar->SetVisibility(ESlateVisibility::Visible);
		TimeBar->SetVisibility(ESlateVisibility::HitTestInvisible);
		TimeBar->SetPercent(HoldTime / RequiredHoldTime);
		if(TimeBar->GetPercent() >= 1)
		{
			TimeBar->SetFillColorAndOpacity(FLinearColor::Red);
		}
	}
}
