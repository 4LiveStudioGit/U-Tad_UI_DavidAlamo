// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadBar.h"

#include "Crosshair.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "../TP_WeaponComponent.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

void UReloadBar::NativeConstruct()
{
	Super::NativeConstruct();
	if(ReloadBar)
		{
			ReloadBar->SetPercent(0.f);
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PlayerCharacter = Cast<AUTAD_UI_FPSCharacter>(PlayerController->GetPawn());
			PlayerCharacter->OnTakeWeapon.BindUObject(this, &UReloadBar::HasWeapon);
		
			
	}
}

void UReloadBar::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UReloadBar::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UReloadBar::UpdateReloadBarValue(float NewValue)
{
	if(ReloadBar)
	{
		ReloadBar->SetPercent(NewValue);
	}
}

void UReloadBar::CancelReload()
{
	ReloadBar->SetPercent(0.f);
}

void UReloadBar::HasWeapon()
{
	UTP_WeaponComponent* WeaponComponent = PlayerCharacter->GetAttachedWeaponComponent();
	if (WeaponComponent)
	{
		// Suscribirse al delegado de disparo
		WeaponComponent->OnReloadTimer.BindUObject(this, &UReloadBar::UpdateReloadBarValue);
		WeaponComponent->OnReloadCanceled.BindUObject(this, &UReloadBar::CancelReload);
			
	}
}
