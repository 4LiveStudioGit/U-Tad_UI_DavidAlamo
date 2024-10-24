// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTAD_UI_FPSCharacter.h"
#include "UTAD_UI_FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// UI
#include "UTAD_UI_FPS_Enemy.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/GameOver.h"
#include "UI/PlayerHUD.h"
#include "UI/AbilityTree/AblityTree.h"

//////////////////////////////////////////////////////////////////////////
// AUTAD_UI_FPSCharacter

AUTAD_UI_FPSCharacter::AUTAD_UI_FPSCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AUTAD_UI_FPSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(Controller);
	//Add Input Mapping Context
	if ( PlayerController )
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Setup Player HUD
	if (PlayerHUDWidget)
	{
		PlayerHUDInstance = CreateWidget<UPlayerHUD>(GetWorld(), PlayerHUDWidget);
		PlayerHUDInstance->AddToViewport();
		PlayerHUDInstance->ShowNoWeapon();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player HUD Widget not assigned to UTAD_UI_FPSCharacter"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player HUD Widget not assigned to UTAD_UI_FPSCharacter"));
	}
}

void AUTAD_UI_FPSCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CrosshairEnemyDetection();
}

//////////////////////////////////////////////////////////////////////////// Input

void AUTAD_UI_FPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUTAD_UI_FPSCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUTAD_UI_FPSCharacter::Look);

		//AbilityTree
		EnhancedInputComponent->BindAction(AbilityTreeAction, ETriggerEvent::Triggered, this, &AUTAD_UI_FPSCharacter::ToggleAbilityTree);
	}
}


void AUTAD_UI_FPSCharacter::CrosshairEnemyDetection()
{
	// Obtener el mundo actual
	UWorld* World = GetWorld();

	// Establecer el punto final del LineTrace (una distancia en frente del jugador)
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * 10000.0f); // 10000 unidades hacia adelante

	// Estructura que contendrá el resultado del trace
	FHitResult HitResult;

	// Parámetros para ignorar ciertos actores, como el jugador
	FCollisionQueryParams TraceParams(FName(TEXT("CrosshairTrace")), true, this);

	// Realizar el LineTrace
	bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, TraceParams);

	// Si impacta algo
	if (bHit)
	{
		// Verificar si el objeto impactado es un enemigo
		AUTAD_UI_FPS_Enemy* Enemy = Cast<AUTAD_UI_FPS_Enemy>(HitResult.GetActor());
		if (Enemy )
		{
			OnCrosshairOverEnemy.ExecuteIfBound(true);
		}
		else
		{
			OnCrosshairOverEnemy.ExecuteIfBound(false);
		}
	}
	else
		{
			OnCrosshairOverEnemy.ExecuteIfBound(false);	
		}
	
}

void AUTAD_UI_FPSCharacter::ToggleAbilityTree()
{
	if(!AbilityTreeInstance)
	{
		AbilityTreeInstance = CreateWidget<UAblityTree>(GetWorld(), AbilityTreeWidget);
		AbilityTreeInstance->AddToViewport(1);
		AbilityTreeInstance->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		// Coloca el foco en el primer widget
		FirstWidget = Cast<UWidget>(AbilityTreeInstance->GetWidgetFromName(TEXT("WB_Ammo1")));
		PlayerController = Cast<APlayerController>(GetController());
		PlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController,FirstWidget, EMouseLockMode::LockInFullscreen, false);
	
	}
	else
	{
		AbilityTreeInstance->SetVisibility(ESlateVisibility::Hidden);
		UWidgetBlueprintLibrary:: SetInputMode_GameOnly(PlayerController,false);
		PlayerController->SetShowMouseCursor(false);
		AbilityTreeInstance->RemoveFromParent();
		AbilityTreeInstance = nullptr;
	}
	
}

int32 AUTAD_UI_FPSCharacter::GetAbilityPoints() const
{
	return abilityPoints;
}

bool AUTAD_UI_FPSCharacter::SetAbilityPoints(int32 NewAbilityPoints)
{
	if(abilityPoints >= NewAbilityPoints)
	{
		abilityPoints -= NewAbilityPoints;
		OnAbilityPointsChanged.ExecuteIfBound();
		return true;
	}
	return false;
}

void AUTAD_UI_FPSCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AUTAD_UI_FPSCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AUTAD_UI_FPSCharacter::SetHealth(int NewHealth)
{
	int ClampedNewHealth = FMath::Clamp(NewHealth, 0, MaxHealth);
	if (ClampedNewHealth != Health)
	{
		Health = ClampedNewHealth;
		OnHealthChanged.ExecuteIfBound(Health, MaxHealth);
		OnPlayerHit.ExecuteIfBound();
	
		if (Health <= 0)
		{
			if(GameOverWidget)
			{
				GameOverInstance = CreateWidget<UGameOver>(GetWorld(), GameOverWidget);
				GameOverInstance->AddToViewport();
				GameOverInstance->Show();
			}
		}
	}
}

int AUTAD_UI_FPSCharacter::GetHealth()
{
	return Health;
}

void AUTAD_UI_FPSCharacter::SetMaxHealth(int NewMaxHealth)
{
	MaxHealth = FMath::Max(0, NewMaxHealth);
}

int AUTAD_UI_FPSCharacter::GetMaxHealth()
{
	return MaxHealth;
}

void AUTAD_UI_FPSCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
	if(bHasRifle)
	{
		PlayerHUDInstance->ShowAll();
		OnTotalBulletsChanged.ExecuteIfBound(TotalBullets);
		OnTakeWeapon.ExecuteIfBound();
	}
}

bool AUTAD_UI_FPSCharacter::GetHasRifle()
{
	return bHasRifle;
}

void AUTAD_UI_FPSCharacter::SetTotalBullets(int NewTotalBullets)
{
	TotalBullets = NewTotalBullets;
	OnTotalBulletsChanged.ExecuteIfBound(TotalBullets);
	
}

int AUTAD_UI_FPSCharacter::GetTotalBullets()
{
	return TotalBullets;
}

void AUTAD_UI_FPSCharacter::AddBullets(int Bullets)
{
	TotalBullets += Bullets;
}

void AUTAD_UI_FPSCharacter::SetAttachedWeaponComponent(UTP_WeaponComponent* WeaponComponent)
{
	AttachedWeaponComponent = WeaponComponent;
}
