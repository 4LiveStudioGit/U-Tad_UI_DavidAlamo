// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "Components/ProgressBar.h"
#include "Math/Color.h"
#include "Styling/SlateColor.h"

#define BLINK_ANIMATION_TIME 1.f
#define BLINK_THRESHOLD 0.75f

void UPlayerHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if(bIsLowHealth)
	{
		LowHealthBlink();
	}
}

void UPlayerHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AUTAD_UI_FPSCharacter* PlayerCharacter = Cast<AUTAD_UI_FPSCharacter>(PlayerController->GetPawn());
	PlayerHealthBar->SetPercent(1.f);
	HealthBarStyle.BackgroundImage.TintColor = FLinearColor(0,0,0,0.5);
	PlayerHealthBar->SetWidgetStyle(HealthBarStyle);

	if (PlayerCharacter)
	{
		// Suscribirse al delegado
		PlayerCharacter->OnHealthChanged.BindUObject(this, &UPlayerHealthBar::UpdatePlayerHealthBar);
	}
}

void UPlayerHealthBar::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UPlayerHealthBar::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerHealthBar::UpdatePlayerHealthBar(int NewHealth, int MaxHealth)
{
	float HealthPercentage = (float)NewHealth / (float)MaxHealth;
	PlayerHealthBar->SetPercent(HealthPercentage);

	if (HealthPercentage <= BLINK_THRESHOLD)
	{
		bIsLowHealth = true;
	}
	else
	{
		bIsLowHealth = false;
	}
}

void UPlayerHealthBar::LowHealthBlink()
{


	BlinkTimer += GetWorld()->GetDeltaSeconds();
	if (BlinkTimer >= BLINK_ANIMATION_TIME)
	{
		BlinkTimer = 0.f;
		if (bBlinkTurningRed)
		{
			HealthBarStyle.BackgroundImage.TintColor = FLinearColor(1,0,0,0.5);
			PlayerHealthBar->SetWidgetStyle(HealthBarStyle);
			bBlinkTurningRed = false;
		}
		else
		{
			HealthBarStyle.BackgroundImage.TintColor = FLinearColor(0,0,0,0.5);
			PlayerHealthBar->SetWidgetStyle(HealthBarStyle);
			bBlinkTurningRed = true;
		}
	}
	
	
}
