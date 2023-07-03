// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGroup.h"
#include "Components/SphereComponent.h"
#include "TopDowner/EnemyRobot.h"

// Sets default values
AEnemyGroup::AEnemyGroup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = DefaultSceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DebugMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	Detection = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	Detection->SetupAttachment(RootComponent);
	Detection->OnComponentBeginOverlap.AddDynamic(this, &AEnemyGroup::OnBeginOverlap);
	Detection->OnComponentEndOverlap.AddDynamic(this, &AEnemyGroup::OnEndOverlap);
}

void AEnemyGroup::MergeAnotherGroup(AEnemyGroup* GroupToMergeIn)
{
	IsBeingMerged = true;

	for(const auto Enemy : EnemiesInRange)
	{
		Enemy->GroupImAPartOf = this;
	}

	EnemiesInRange.Append(GroupToMergeIn->EnemiesInRange);
	GroupToMergeIn->Destroy();
}

void AEnemyGroup::UpdateUnitCosts()
{
	auto Cost {0};
	for(const auto Enemy : EnemiesInRange)
	{
		Cost += Enemy->UnitGroupCost;
	}
	CostOfUnits = Cost;
}

void AEnemyGroup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector DesiredPosition;

	for(const auto Enemy : EnemiesInRange)
	{
		const auto EnemyPos = Enemy->GetActorLocation();
		DesiredPosition += EnemyPos;
		DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), EnemyPos, 5.0, FColor::Red, false);
	}

	DesiredPosition /= EnemiesInRange.Num();

	SetActorLocation(
		FMath::Lerp(GetActorLocation(), DesiredPosition, DeltaSeconds * 15.0));
}

void AEnemyGroup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Enemy = Cast<AEnemyRobot>(OtherActor))
	{
		EnemiesInRange.AddUnique(Enemy);
		Enemy->GroupImAPartOf = this;

		//TODO bind on dead
		UpdateUnitCosts();
	}

	if (auto OtherGroup = Cast<AEnemyGroup>(OtherActor))
	{
		if (IsBeingMerged == false)
		{
			MergeAnotherGroup(OtherGroup);
		}
	}
}

void AEnemyGroup::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto Enemy = Cast<AEnemyRobot>(OtherActor))
	{
		EnemiesInRange.Remove(Enemy);
		Enemy->GroupImAPartOf = nullptr;
		
		UpdateUnitCosts();
	}
}
