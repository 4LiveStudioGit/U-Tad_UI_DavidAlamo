// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMarker.h"

#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

void UPlayerMarker::NativeConstruct()
{
	Super::NativeConstruct();
	Border->SetBrushColor(FLinearColor(255,0,0,0));
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AUTAD_UI_FPSCharacter* PlayerCharacter = Cast<AUTAD_UI_FPSCharacter>(PlayerController->GetPawn());
	

	if (PlayerCharacter)
	{
		// Suscribirse al delegado
		PlayerCharacter->OnPlayerHit.BindUObject(this, &UPlayerMarker::HitReact);
	}
}

void UPlayerMarker::HitReact()

{
	Border->SetBrushColor(FLinearColor(255,0,0,0.5));
	PlayAnimation(Hit);
}
