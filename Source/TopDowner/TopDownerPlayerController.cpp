// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownerPlayerController.h"

#include "EnemyRobot.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "TopDownerCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AI/Combat/CombatController.h"
#include "AI/Combat/CombatControllerSubsystem.h"
#include "Kismet/GameplayStatics.h"

ATopDownerPlayerController::ATopDownerPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ATopDownerPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	auto GASComponent = Cast<ATopDownerCharacter>(GetPawn())->AbilitySystemComponent;
	//const auto FireAbilitySpec = GASComponent->BuildAbilitySpecFromClass(FireAbility, 0, 5);
	//GASComponent->GiveAbility(FireAbilitySpec);
}

void ATopDownerPlayerController::StopRandomSpawning()
{
	if (auto CombatController = UCombatControllerFunctionLibrary::GetCombatController(this))
	{
		CombatController->DesiredEnemies.Empty();
	}
}
void ATopDownerPlayerController::KillAllEnemies()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyRobot::StaticClass(), FoundActors);
}

void ATopDownerPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Get the player controller
		APlayerController* PC = Cast<APlayerController>(this);
		
		//Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			Subsystem->AddMappingContext(AimingMappingContext, 0);
			Subsystem->AddMappingContext(SpecialMappingContext, 0);
		}
		
		//Setup Movement
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATopDownerPlayerController::Move);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATopDownerPlayerController::Fire);
        EnhancedInputComponent->BindAction(MouseAimAction, ETriggerEvent::Triggered, this, &ATopDownerPlayerController::Aim);
        //Setup Aim
        EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ATopDownerPlayerController::BeginAim);
        EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ATopDownerPlayerController::EndAim);

		EnhancedInputComponent->BindAction(SpecialAction, ETriggerEvent::Triggered, this, &ATopDownerPlayerController::Special);
		EnhancedInputComponent->BindAction(NextSpecialAction, ETriggerEvent::Triggered, this, &ATopDownerPlayerController::NextSpecial);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ATopDownerPlayerController::Dash);
	}
}

void ATopDownerPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ATopDownerPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ATopDownerPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ATopDownerPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ATopDownerPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ATopDownerPlayerController::Move(const FInputActionValue& Value)
{
	Cast<ATopDownerCharacter>(GetPawn())->Move(Value);
}

void ATopDownerPlayerController::Special(const FInputActionValue& Value)
{
	Cast<ATopDownerCharacter>(GetPawn())->Special(Value);
}

void ATopDownerPlayerController::NextSpecial(const FInputActionValue& Value)
{
	const auto PlayerChar = Cast<ATopDownerCharacter>(GetPawn());
	if (Value.GetMagnitude() > 0.0)
	{
		PlayerChar->OnNextItem();
	}
	else if (Value.GetMagnitude() < 0.0)
	{
		PlayerChar->OnPrevItem();
	}
}

void ATopDownerPlayerController::PrevSpecial(const FInputActionValue& Value)
{
	Cast<ATopDownerCharacter>(GetPawn())->OnPrevItem();
}

void ATopDownerPlayerController::Dash(const FInputActionValue& Value)
{
	Cast<ATopDownerCharacter>(GetPawn())->Dash(Value);
}

void ATopDownerPlayerController::BeginAim(const FInputActionValue& Value)
{
	Cast<ATopDownerCharacter>(GetPawn())->BeginAim(Value);
}

void ATopDownerPlayerController::EndAim(const FInputActionValue& Value)
{
	Cast<ATopDownerCharacter>(GetPawn())->EndAim(Value);
}

void ATopDownerPlayerController::Fire(const FInputActionValue& Value)
{
	Cast<ATopDownerCharacter>(GetPawn())->Fire(Value);
}

void ATopDownerPlayerController::Aim(const FInputActionValue& Value)
{
	Cast<ATopDownerCharacter>(GetPawn())->Aim(Value);
}
