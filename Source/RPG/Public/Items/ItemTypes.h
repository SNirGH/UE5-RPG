#pragma once

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_None UMETA(DisplayName = "None"),
	EIT_Weapon UMETA(DisplayName = "Weapon"),
	EIT_Potion UMETA(DisplayName = "Potion")
};

UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Hovering UMETA(DisplayName = "Hovering"),
	EIS_Equipped UMETA(DisplayName = "Equipped")
};