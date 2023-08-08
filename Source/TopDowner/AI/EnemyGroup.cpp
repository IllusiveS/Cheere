// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGroup.h"

#include "Combat/CombatControllerSubsystem.h"
#include "Components/SphereComponent.h"
#include "TopDowner/EnemyRobot.h"

// Sets default values
AEnemyGroup::AEnemyGroup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = DefaultSceneRoot;

	Detection = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	Detection->SetupAttachment(RootComponent);
	Detection->OnComponentBeginOverlap.AddDynamic(this, &AEnemyGroup::OnBeginOverlap);
	Detection->OnComponentEndOverlap.AddDynamic(this, &AEnemyGroup::OnEndOverlap);
	Detection->SetCollisionResponseToAllChannels(ECR_Ignore);
	Detection->SetCollisionObjectType(ECC_GameTraceChannel4);
	Detection->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Detection->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);
	Detection->InitSphereRadius(1000.0);
	Detection->SetGenerateOverlapEvents(true);
	Detection->SetHiddenInGame(true);
}

void AEnemyGroup::MergeAnotherGroup(AEnemyGroup* GroupToMergeIn)
{
	GroupToMergeIn->IsBeingMerged = true;

	if (GroupToMergeIn->IsActivated)
	{
		IsActivated = true;
	}
	
	for(const auto Enemy : GroupToMergeIn->EnemiesInRange)
	{
		Enemy->GroupImAPartOf = this;
		if (IsActivated == true)
		{
			Enemy->ActivateLow();
		}
	}

	if(IsActivated)
	{
		for(const auto Enemy : EnemiesInRange)
		{
			Enemy->ActivateLow();
		}
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

void AEnemyGroup::BeginPlay()
{
	Super::BeginPlay();
	if (auto CombatController = UCombatControllerFunctionLibrary::GetCombatController(GetWorld()))
	{
		CombatController->AddGroupToCombat(this);
	}

	FTimerHandle Handle;
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &AEnemyGroup::CheckForSelfDestruction);
	GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, 0.1f, true);
}

void AEnemyGroup::BeginDestroy()
{

	for (auto enemy : EnemiesInRange)
	{
		enemy->GroupImAPartOf == nullptr;
	}
	
	if (auto CombatController = UCombatControllerFunctionLibrary::GetCombatController(GetWorld()))
	{
		CombatController->RemoveGroupFromCombat(this);
	}
	
	Super::BeginDestroy();
}

void AEnemyGroup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (auto CombatController = UCombatControllerFunctionLibrary::GetCombatController(GetWorld()))
	{
		CombatController->RemoveGroupFromCombat(this);
	}
	
	Super::EndPlay(EndPlayReason);
}

void AEnemyGroup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector DesiredPosition{0.0f};

	if (EnemiesInRange.IsEmpty()) return;
	
	for(const auto Enemy : EnemiesInRange)
	{
		const auto EnemyPos = Enemy->GetActorLocation();
		DesiredPosition += EnemyPos;
		//DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), EnemyPos, 5.0, FColor::Red, false, -1, SDPG_World, 5.0);
	}

	DesiredPosition /= EnemiesInRange.Num();

	SetActorLocation(
		FMath::Lerp(GetActorLocation(), DesiredPosition, DeltaSeconds * 15.0));

	if(OrderedPosition.Length() > 1.0)
	{
		//DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), OrderedPosition, 15.0, FColor::Blue, false, -1, SDPG_World, 7.0);
	}

	EnemiesInRange = EnemiesInRange.FilterByPredicate([this](auto Enemy){ return Enemy->GroupImAPartOf == this;});
}

void AEnemyGroup::ActivateGroup()
{
	IsActivated = true;
	for(const auto Enemy : EnemiesInRange)
	{
		IAICombatInterface::Execute_ActivateLow(Enemy);
	}
}

void AEnemyGroup::SetGroupTarget(FVector target)
{
	for(const auto Enemy : EnemiesInRange)
	{
		Enemy->SetTargetPosition(target);
	}
	OrderedPosition = target;
	UE_LOG(LogTemp, Warning, TEXT("Setting target to %s"), *target.ToString());
}

bool AEnemyGroup::CanJoinGroup(AEnemyRobot* Enemy)
{
	if (Enemy->GroupImAPartOf != nullptr && Enemy->GroupImAPartOf->IsValidLowLevel()) return false;
	UpdateUnitCosts();
	return (CostOfUnits + Enemy->UnitGroupCost) <= MaxCostOfUnits;
}

bool AEnemyGroup::CanBeMerged(AEnemyGroup* OtherGroup)
{
	UpdateUnitCosts();
	OtherGroup->UpdateUnitCosts();
	return ((OtherGroup->CostOfUnits + CostOfUnits) <= MaxCostOfUnits);
}

void AEnemyGroup::OrderNeedlessUnitsOutOfGroup()
{
	if (isRemovingNeedlessUnit) return;
	EnemiesInRange.Sort([](auto& Enemy1, auto& Enemy2)
	{
		return Enemy1.UnitGroupCost < Enemy2.UnitGroupCost;
	});
	EnemiesInRange[0]->GoAway();
	EnemiesInRange.RemoveAt(0);

	isRemovingNeedlessUnit = true;
	
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &AEnemyGroup::AllowRemovalOfNeedlessUnits, 2, false);

	UpdateUnitCosts();
}

void AEnemyGroup::ReactToEnemyDead(AEnemyRobot* Enemy)
{
	EnemiesInRange.Remove(Enemy);
	if(EnemiesInRange.Num() < 1) Destroy();
}

void AEnemyGroup::AllowRemovalOfNeedlessUnits()
{
	isRemovingNeedlessUnit = false;	
}

void AEnemyGroup::CheckForSelfDestruction()
{
	if (EnemiesInRange.IsEmpty()) Destroy();
}

void AEnemyGroup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Enemy = Cast<AEnemyRobot>(OtherActor))
	{
		if (Enemy->IsDead) return;
		if (CanJoinGroup(Enemy) == false) return;
		if (Enemy->GroupImAPartOf != nullptr)
		{
			Enemy->GroupImAPartOf->EnemiesInRange.Remove(Enemy);
		}
		EnemiesInRange.AddUnique(Enemy);
		Enemy->GroupImAPartOf = this;
		Enemy->OnEnemyDead.AddUniqueDynamic(this, &AEnemyGroup::ReactToEnemyDead);
		
		UpdateUnitCosts();

		if(CostOfUnits > MaxCostOfUnits)
		{
			OrderNeedlessUnitsOutOfGroup();
		}
	}

	if (auto OtherGroup = Cast<AEnemyGroup>(OtherActor))
	{
		if (OtherGroup == this) return;
		if (IsBeingMerged == false && CanBeMerged(OtherGroup) && OtherGroup->CanBeMerged(this))
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
		// EnemiesInRange.Remove(Enemy);
		// Enemy->OnEnemyDead.RemoveDynamic(this, &AEnemyGroup::ReactToEnemyDead);
		// Enemy->GroupImAPartOf = nullptr;
		//
		// UpdateUnitCosts();
	}
}
