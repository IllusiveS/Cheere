#pragma once

UENUM(BlueprintType)
enum class EActivationType : uint8
{
	None,
	Low,
	High
};

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Basic,
	Melee,
	Special,
	None
};