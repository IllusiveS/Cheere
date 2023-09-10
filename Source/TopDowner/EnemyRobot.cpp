// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRobot.h"

#include "MotionWarpingComponent.h"
#include "AI/EnemyGroup.h"
#include "AI/Combat/CombatControllerSubsystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/TopDownerAbilitySystemComponent.h"
#include "GAS/AttributeSets/BasicCharacterAttributeSet.h"
#include "GAS/AttributeSets/FearAttributeSet.h"
#include "GAS/AttributeSets/MovementAttributeSet.h"

// Sets default values
AEnemyRobot::AEnemyRobot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UTopDownerAbilitySystemComponent>(TEXT("AbilityComp"));
	BasicEntityAttributes = CreateDefaultSubobject<UBasicCharacterAttributeSet>(TEXT("HealthAttributes"));
	FearAttributes = CreateDefaultSubobject<UFearAttributeSet>(TEXT("FearAttributes"));
	MovementAttributes = CreateDefaultSubobject<UMovementAttributeSet>(TEXT("MovementAttributes"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributes->GetMaxWalkSpeedAttribute())
		.AddUObject(this, &AEnemyRobot::WalkSpeedChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributes->GetMaxAccelerationAttribute())
		.AddUObject(this, &AEnemyRobot::MaxAccelerationChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributes->GetGroundFrictionAttribute())
		.AddUObject(this, &AEnemyRobot::GroundFrictionChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributes->GetBrakingDecelerationWalkingAttribute())
    	.AddUObject(this, &AEnemyRobot::BrakingDecelerationWalkingChanged);	
}

void AEnemyRobot::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	Super::GetActorEyesViewPoint(OutLocation, OutRotation);
	OutLocation = GetMesh()->GetSocketLocation("HeadSocket");
	OutRotation = GetMesh()->GetSocketRotation("HeadSocket");
}

// Called when the game starts or when spawned
void AEnemyRobot::BeginPlay()
{
	Super::BeginPlay();

	if (auto CombatController = UCombatControllerFunctionLibrary::GetCombatController(GetWorld()))
	{
		CombatController->AddEnemyToCombat(this);
	}
}

void AEnemyRobot::WalkSpeedChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}

void AEnemyRobot::MaxAccelerationChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxAcceleration = Data.NewValue;
}

void AEnemyRobot::GroundFrictionChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->GroundFriction = Data.NewValue;
}

void AEnemyRobot::BrakingDecelerationWalkingChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->BrakingDecelerationWalking = Data.NewValue;
}

// Called every frame
void AEnemyRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GroupImAPartOf != nullptr && GroupImAPartOf->IsValidLowLevel() == false)
	{
		GroupImAPartOf = nullptr;
	}
}

// Called to bind functionality to input
void AEnemyRobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemyRobot::IsActivated() const
{
	return ActivationType != EActivationType::None;
}

void AEnemyRobot::ChangeGroup(AEnemyGroup* Group)
{
	//if (GroupImAPartOf)
	
	GroupImAPartOf = Group;
}

bool AEnemyRobot::ActivateByEnum_Implementation(EActivationType Activation)
{
	ActivationType = Activation;
	OnEnemyActivated.Broadcast(this, Activation);
	return true;
}

bool AEnemyRobot::ActivateLow_Implementation()
{
	return ActivateByEnum(EActivationType::Low);
}

bool AEnemyRobot::ActivateHigh_Implementation()
{
	return ActivateByEnum(EActivationType::High);
}

bool AEnemyRobot::ActivateNone_Implementation()
{
	return ActivateByEnum(EActivationType::None);
}
