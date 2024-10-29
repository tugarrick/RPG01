// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemName : uint8
{
	None UMETA(DisplayName = "None"),

	Sword_Lv1 UMETA(DisplayName = "Sword_Lv1"),
	WoodShield UMETA(DisplayName = "WoodShield"),
	SteelHelmet UMETA(DisplayName = "SteelHelmet"),

	PlateArmor UMETA(DisplayName = "PlateArmor"),
	PlateGloves UMETA(DisplayName = "PlateGloves"),
	PlatePants UMETA(DisplayName = "PlatePants"),
	PlateBoots UMETA(DisplayName = "PlateBoots"),

	IronAxe UMETA(DisplayName = "IronAxe"),
	StoneAxe UMETA(DisplayName = "StoneAxe")
};

class RPG01_API ItemName
{
public:
	ItemName();
	~ItemName();
};
