// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ERarity : uint8
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary"),
	Mythic UMETA(DisplayName = "Mythic"),
	Relic UMETA(DisplayName = "Relic"),
	Masterwork UMETA(DisplayName = "Masterwork"),
	Eternal UMETA(DisplayName = "Eternal"),

};
class RPG01_API Rarity
{
public:
	Rarity();
	~Rarity();
};
