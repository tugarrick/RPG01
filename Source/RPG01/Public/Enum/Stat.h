// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EStat : uint8
{
	Health UMETA(DisplayName = "Health"),
	Stamina UMETA(DisplayName = "Stamina"),
	Mana UMETA(DisplayName = "Mana"),
	Armor UMETA(DisplayName = "Armor"),
	PhysicalDamage UMETA(DisplayName = "Physical Damage"),
	MagicalDamage UMETA(DisplayName = "Magical Damage"),
	MovementSpeed UMETA(DisplayName = "Movement Speed"),
	AttackSpeed UMETA(DisplayName = "Attack Speed"),
	Cooldown UMETA(DisplayName = "Cooldown"),
	StaminaRegen UMETA(DisplayName = "Stamina Regen"),
	ManaRegen UMETA(DisplayName = "Mana Regen"),

};

class RPG01_API Stat
{
public:
	Stat();
	~Stat();
};
