#include "BatterySlot.h"

#include "FlowComponent.h"

ABatterySlot::ABatterySlot()
{
	Flow = CreateDefaultSubobject<UFlowComponent>(TEXT("Flow"));
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(DefaultSceneRoot);

	Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Cylinder->SetupAttachment(GetRootComponent());
}
