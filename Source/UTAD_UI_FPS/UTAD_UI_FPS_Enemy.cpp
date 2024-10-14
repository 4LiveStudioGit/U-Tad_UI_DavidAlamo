// Fill out your copyright notice in the Description page of Project Settings.


#include "UTAD_UI_FPS_Enemy.h"

#include "UTAD_UI_FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/EnemyHealthBar.h"
#include "Components/WidgetComponent.h"

void AUTAD_UI_FPS_Enemy::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;
	Super::BeginPlay();

	EnemyHealthBarComponent = FindComponentByClass<UWidgetComponent>();
	if (EnemyHealthBarComponent)
	{
		EnemyHealthBarComponent->SetVisibility(false);
		EnemyHealthBarComponent->CastShadow = false;
	}
}

void AUTAD_UI_FPS_Enemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector EnemyHealthBarVector = EnemyHealthBarComponent->GetComponentLocation();
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FTransform CameraTransform = PlayerCameraManager->GetTransform();
	FRotator CameraRotation = UKismetMathLibrary::FindLookAtRotation(EnemyHealthBarVector,CameraTransform.GetLocation());
	EnemyHealthBarComponent->SetWorldRotation(CameraRotation);
}

void AUTAD_UI_FPS_Enemy::SetHealth(int NewHealth)
{

	Health = FMath::Clamp(NewHealth, 0, MaxHealth);
	if(EnemyHealthBarComponent)
	{
		if(!EnemyHealthBarComponent->IsWidgetVisible())
		{
			EnemyHealthBarComponent->SetVisibility(true);
		}
		UEnemyHealthBar* EnemyHealthBar = Cast<UEnemyHealthBar>(EnemyHealthBarComponent->GetUserWidgetObject());
		EnemyHealthBar->UpdateEnemyHealthBarValue(Health, MaxHealth);
	}
	if (Health == 0)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AUTAD_UI_FPSCharacter* Player = Cast<AUTAD_UI_FPSCharacter>(PlayerController->GetPawn());
		Player->SetAbilityPoints(-99);
		Destroy();
	}
}

int AUTAD_UI_FPS_Enemy::GetHealth()
{
	return Health;
}

void AUTAD_UI_FPS_Enemy::SetMaxHealth(int NewMaxHealth)
{
	MaxHealth = FMath::Max(0, NewMaxHealth);
}

int AUTAD_UI_FPS_Enemy::GetMaxHealth()
{
	return MaxHealth;
}