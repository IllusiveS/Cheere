// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlowActor.generated.h"

UCLASS()
class TOPDOWNER_API AFlowActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlowActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TObjectPtr<class USceneComponent> SceneRootComponent;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true", DisplayPriority="1"))
	TObjectPtr<class UFlowComponent> FlowComponent;

# if WITH_EDITORONLY_DATA

	/** Billboard used to see the trigger in the editor */
	UPROPERTY(Category = TriggerBase, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBillboardComponent> SpriteComponent;

# endif
};
