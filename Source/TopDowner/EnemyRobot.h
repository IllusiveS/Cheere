// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayEffectTypes.h"
#include "AI/Combat/CombatController.h"
#include "EnemyRobot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyRobotDelegate, AEnemyRobot*, Robot);

UCLASS()
class TOPDOWNER_API AEnemyRobot : public ACharacter, public IAICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyRobot();

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void WalkSpeedChanged(const FOnAttributeChangeData& Data);
	virtual void MaxAccelerationChanged(const FOnAttributeChangeData& Data);
	virtual void GroundFrictionChanged(const FOnAttributeChangeData& Data);
	virtual void BrakingDecelerationWalkingChanged(const FOnAttributeChangeData& Data);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Attributes")
	TObjectPtr<class UBasicCharacterAttributeSet> BasicEntityAttributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Attributes")
	TObjectPtr<class UFearAttributeSet> FearAttributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Attributes")
	TObjectPtr<class UMovementAttributeSet> MovementAttributes;
	
	UPROPERTY(Category=Abilities, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UTopDownerAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class AEnemyGroup> GroupImAPartOf;

	UFUNCTION(BlueprintCallable)
	void ChangeGroup(class AEnemyGroup* Group);
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FVector LastDmgDir;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int UnitGroupCost {1};

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FEnemyRobotDelegate OnEnemyDead;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetTargetPosition(FVector targetPos);

	UFUNCTION(BlueprintImplementableEvent)
	void GoAway();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UEnvQuery* SetGroupTargetQuery;
};
