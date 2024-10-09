// Fill out your copyright notice in the Description page of Project Settings.


#include "Crosshair.h"

#include "Animation/WidgetAnimation.h"
#include "Components/Image.h"
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

	
}

void UCrosshair::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(!WeaponDelegateBound)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AUTAD_UI_FPSCharacter* PlayerCharacter = Cast<AUTAD_UI_FPSCharacter>(PlayerController->GetPawn());

		//Suscribirse al delegado de deteccion de enemigos
		PlayerCharacter->OnCrosshairOverEnemy.BindUObject(this, &UCrosshair::ChangeColor);
		

		UTP_WeaponComponent* WeaponComponent = PlayerCharacter->GetAttachedWeaponComponent();
		if (WeaponComponent)
		{
			// Suscribirse al delegado de disparo
			WeaponComponent->OnFireWeapon.BindUObject(this, &UCrosshair::PlayAnim);
			WeaponDelegateBound = true;
		}
	}
}

void UCrosshair::PlayAnim()
{
	PlayAnimation(Fire);
	
}

void UCrosshair::ChangeColor(bool CrosshairOverEnemy)
{
	if(CrosshairOverEnemy)
	{
		Crosshair->SetColorAndOpacity(FLinearColor::Red);
	}
	else
	{
		Crosshair->SetColorAndOpacity(FLinearColor::White);
	}
}
