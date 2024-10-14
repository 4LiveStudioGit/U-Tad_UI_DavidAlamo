// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowAbilityPoints.h"

#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

void UShowAbilityPoints::NativeConstruct()
{
	Super::NativeConstruct();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerCharacter = Cast<AUTAD_UI_FPSCharacter>(PlayerController->GetPawn());
	puntos = PlayerCharacter->GetAbilityPoints();
	PlayerCharacter->OnAbilityPointsChanged.BindUObject(this,&UShowAbilityPoints::UpdateAbilityPoints);
	UpdateAbilityPoints();
	
}


void UShowAbilityPoints::UpdateAbilityPoints()
{
	if(AbilityPoints)
	{
		puntos = PlayerCharacter->GetAbilityPoints();
		AbilityPoints->SetText(FText::FromString(FString::FromInt(puntos)));
	}
}
