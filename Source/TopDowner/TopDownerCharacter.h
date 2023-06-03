// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "TopDownerCharacter.generated.h"

UCLASS(Blueprintable)
class ATopDownerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATopDownerCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; };
	
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsAiming {false};
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnFire();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSpecial();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDash();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BeginAiming();

	UFUNCTION(BlueprintImplementableEvent)
	void EndAiming();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Attributes")
	TObjectPtr<class UBasicCharacterAttributeSet> BasicEntityAttributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Attributes")
	TObjectPtr<class UMovementAttributeSet> MovementAttributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Attributes")
	TObjectPtr<class UDodgeAttributeSet> DodgeAttributes;
	
	UPROPERTY(Category=Abilities, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UTopDownerAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UBackpackComponent> BackpackComponent;
	
private:
	UPROPERTY(Category=Abilities, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UTopDownerGameplayAbility> FireAbility;
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** AimingMappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* AimingMappingContext;
	
	/** AimingMappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FiringMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* AimAction;
	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* EndAimAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MouseAimAction;

public:
	virtual void WalkSpeedChanged(const FOnAttributeChangeData& Data);
	virtual void MaxAccelerationChanged(const FOnAttributeChangeData& Data);
	virtual void GroundFrictionChanged(const FOnAttributeChangeData& Data);
	virtual void BrakingDecelerationWalkingChanged(const FOnAttributeChangeData& Data);
	
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void BeginAim(const FInputActionValue& Value);
	UFUNCTION()
	void EndAim(const FInputActionValue& Value);
	UFUNCTION()
	void Fire(const FInputActionValue& Value);
	UFUNCTION()
	void Special(const FInputActionValue& Value);
	UFUNCTION()
	void Dash(const FInputActionValue& Value);
	UFUNCTION()
	void Aim(const FInputActionValue& Value);
};

