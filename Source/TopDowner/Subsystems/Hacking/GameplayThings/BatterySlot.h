#include "BatterySlot.generated.h"

/** Please add a class description */
UCLASS(Blueprintable, BlueprintType)
class ABatterySlot : public AActor
{
	GENERATED_BODY()
public:
	ABatterySlot();
	
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<class UFlowComponent> Flow;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UStaticMeshComponent> Cylinder;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TArray<class UTopDownerAbilitySystemComponent*> GASInRange;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	bool IsActive;
};
