// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowActor.h"

#include "FlowComponent.h"
#include "Components/BillboardComponent.h"

// Sets default values
AFlowActor::AFlowActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlowComponent = CreateDefaultSubobject<UFlowComponent>(TEXT("Flow"));
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRootComponent);

# if WITH_EDITORONLY_DATA

	SpriteComponent = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));
	if (SpriteComponent)
	{
		// Structure to hold one-time initialization
		struct FConstructorStatics
		{
			ConstructorHelpers::FObjectFinderOptional<UTexture2D> TriggerTextureObject;
			FName ID_Triggers;
			FText NAME_Triggers;
			FConstructorStatics()
				: TriggerTextureObject(TEXT("/Engine/EditorResources/S_Trigger"))
				, ID_Triggers(TEXT("Triggers"))
				, NAME_Triggers(NSLOCTEXT( "SpriteCategory", "Triggers", "Triggers" ))
			{
			}
		};
		static FConstructorStatics ConstructorStatics;

		SpriteComponent->Sprite = ConstructorStatics.TriggerTextureObject.Get();
		SpriteComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
		SpriteComponent->bHiddenInGame = false;
		SpriteComponent->SpriteInfo.Category = ConstructorStatics.ID_Triggers;
		SpriteComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME_Triggers;
		SpriteComponent->bIsScreenSizeScaled = true;
		SpriteComponent->SetupAttachment(GetRootComponent());
	}

# endif
}

// Called when the game starts or when spawned
void AFlowActor::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void AFlowActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

