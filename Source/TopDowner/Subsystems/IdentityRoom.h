// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "IdentityRoom.generated.h"

UCLASS()
class TOPDOWNER_API AIdentityRoom : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnActorEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Sets default values for this actor's properties
	AIdentityRoom();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flow", meta=(DisplayPriority="1"))
	FGameplayTagContainer IdentityTags;

	UPROPERTY(VisibleAnywhere, Category = "Flow", meta=(DisplayPriority="1", DisplayAfter="Transform"))
	TObjectPtr<class UBoxComponent> RoomRange;

	UFUNCTION(CallInEditor, Category = "Flow", meta=(DisplayPriority="1", DisplayAfter="Transform"))
	void UpdateFlowComponents();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

# if WITH_EDITORONLY_DATA

	/** Billboard used to see the trigger in the editor */
	UPROPERTY(Category = TriggerBase, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBillboardComponent> SpriteComponent;

# endif
};
