// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	MainHand UMETA(DisplayName = "Main-Hand"),
	Shield UMETA(DisplayName = "Shield"),
	Head UMETA(DisplayName = "Head"),
	Chest UMETA(DisplayName = "Chest"),
	Hands UMETA(DisplayName = "Hands"),
	Legs UMETA(DisplayName = "Legs"),
	Feet UMETA(DisplayName = "Feet"),
};

class RPG01_API ItemType
{
public:
	ItemType();
	~ItemType();
};
