#pragma once

UENUM(BlueprintType)
enum class EActivationType : uint8
{
	None,
	Low,
	High,
	StealBattery
};

UENUM(BlueprintType)
enum EEnemyType : uint8
{
	Basic,
	Melee,
	Special,
	None
};