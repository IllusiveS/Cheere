// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Backpack/BackpackComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/TopDownerAbilitySystemComponent.h"
#include "GAS/AttributeSets/BasicCharacterAttributeSet.h"
#include "GAS/AttributeSets/DodgeAttributeSet.h"
#include "GAS/AttributeSets/MovementAttributeSet.h"
#include "Kismet/KismetMathLibrary.h"

ATopDownerCharacter::ATopDownerCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTopDownerAbilitySystemComponent>(TEXT("AbilityComp"));
	BasicEntityAttributes = CreateDefaultSubobject<UBasicCharacterAttributeSet>(TEXT("HealthAttributes"));
	MovementAttributes = CreateDefaultSubobject<UMovementAttributeSet>(TEXT("MovementAttributes"));
	DodgeAttributes = CreateDefaultSubobject<UDodgeAttributeSet>(TEXT("DodgeAttributes"));

	BackpackComponent = CreateDefaultSubobject<UBackpackComponent>(TEXT("Backpack"));
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributes->GetMaxWalkSpeedAttribute())
		.AddUObject(this, &ATopDownerCharacter::WalkSpeedChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributes->GetMaxAccelerationAttribute())
		.AddUObject(this, &ATopDownerCharacter::MaxAccelerationChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributes->GetGroundFrictionAttribute())
		.AddUObject(this, &ATopDownerCharacter::GroundFrictionChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributes->GetMaxWalkSpeedAttribute())
		.AddUObject(this, &ATopDownerCharacter::BrakingDecelerationWalkingChanged);
	
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

UAbilitySystemComponent* ATopDownerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent; 
}

void ATopDownerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ATopDownerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{

		//Setup Fire
		
	}
}

void ATopDownerCharacter::WalkSpeedChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}

void ATopDownerCharacter::MaxAccelerationChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxAcceleration = Data.NewValue;
}

void ATopDownerCharacter::GroundFrictionChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->GroundFriction = Data.NewValue;
}

void ATopDownerCharacter::BrakingDecelerationWalkingChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->BrakingDecelerationWalking = Data.NewValue;
}

void ATopDownerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(FVector(1.0, 0, 0), MovementVector.Y);
		AddMovementInput(FVector(0.0, 1, 0), MovementVector.X);
	}
}

void ATopDownerCharacter::BeginAim(const FInputActionValue& Value)
{
	IsAiming = true;

	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());
		
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		//Subsystem->RemoveMappingContext(DefaultMappingContext);
		Subsystem->AddMappingContext(FiringMappingContext, 0);
	}

	BeginAiming();
}

void ATopDownerCharacter::EndAim(const FInputActionValue& Value)
{
	IsAiming = false;
	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());
		
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(FiringMappingContext);
		//Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	EndAiming();
}

void ATopDownerCharacter::Fire(const FInputActionValue& Value)
{
	OnFire();
}

void ATopDownerCharacter::Special(const FInputActionValue& Value)
{
	OnSpecial();
}

void ATopDownerCharacter::Dash(const FInputActionValue& Value)
{
	OnDash();
}

void ATopDownerCharacter::Aim(const FInputActionValue& Value)
{
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	
	APlayerController* PC = Cast<APlayerController>(GetController());
	bHitSuccessful = PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful == false)
	{
		return;
	}
	Hit.Location.Z = GetActorLocation().Z;
	auto rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Hit.Location);
	SetActorRotation(rotator);
}
