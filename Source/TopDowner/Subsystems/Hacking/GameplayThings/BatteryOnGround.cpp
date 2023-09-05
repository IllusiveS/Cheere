#include "BatteryOnGround.h"

#include "FlowComponent.h"

ABatteryOnGround::ABatteryOnGround()
{
	Flow = CreateDefaultSubobject<UFlowComponent>(TEXT("Flow"));
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(DefaultSceneRoot);

	Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Cylinder->SetupAttachment(GetRootComponent());
}
