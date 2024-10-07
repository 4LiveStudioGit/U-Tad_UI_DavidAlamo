// Fill out your copyright notice in the Description page of Project Settings.


#include "Crosshair.h"

#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "UTAD_UI_FPS/TP_WeaponComponent.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

void UCrosshair::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCrosshair::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}



void UCrosshair::NativeConstruct()
{
	Super::NativeConstruct();

	if(!WeaponDelegateBound)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AUTAD_UI_FPSCharacter* PlayerCharacter = Cast<AUTAD_UI_FPSCharacter>(PlayerController->GetPawn());
		UTP_WeaponComponent* WeaponComponent = PlayerCharacter->GetAttachedWeaponComponent();
		if (WeaponComponent)
		{
			// Suscribirse al delegado
			WeaponComponent->OnFireWeapon.BindUObject(this, &UCrosshair::playanim);
			WeaponDelegateBound = true;
		}
	}
}

void UCrosshair::playanim()
{
	PlayAnimation(Fire);
}
