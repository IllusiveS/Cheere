// Fill out your copyright notice in the Description page of Project Settings.


#include "IdentityRoom.h"

#include "EngineUtils.h"
#include "FlowComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TopDowner/TopDownerCharacter.h"
#include "TopDowner/AI/Combat/CombatController.h"
#include "TopDowner/AI/Combat/CombatControllerSubsystem.h"

void AIdentityRoom::OnActorEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(auto Player = Cast<ATopDownerCharacter>(OtherActor))
	{
		if (auto CombatController = UCombatControllerFunctionLibrary::GetCombatController(this))
		{
			CombatController->IdentityTags = IdentityTags;
		}
	}
}

// Sets default values
AIdentityRoom::AIdentityRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneRoot);
	
	RoomRange = CreateDefaultSubobject<UBoxComponent>(TEXT("Range"));
	RoomRange->SetupAttachment(GetRootComponent());
	RoomRange->OnComponentBeginOverlap.AddDynamic(this, &AIdentityRoom::OnActorEntered);

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
    				: TriggerTextureObject(TEXT("/Engine/EditorResources/LevelInstance"))
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

void AIdentityRoom::UpdateFlowComponents()
{
	FVector Origin;
	FVector Extends;
	GetActorBounds(false, Origin, Extends);

	
	TArray<UFlowComponent*> Flows;
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (auto FlowComp = ActorItr->GetComponentByClass<UFlowComponent>())
		{
			Flows.Add(FlowComp);
		}
	}

	for (const auto Flow : Flows)
	{
		const auto Pos = Flow->GetOwner()->GetActorLocation();
		Flow->IdentityTags.RemoveTags(IdentityTags);
		
		if (UKismetMathLibrary::IsPointInBox(Pos, Origin, Extends))
		{
			Flow->IdentityTags.AppendTags(IdentityTags);
		}
	}
}

// Called when the game starts or when spawned
void AIdentityRoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIdentityRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

