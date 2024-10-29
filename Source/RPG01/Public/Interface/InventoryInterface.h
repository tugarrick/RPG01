// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

class UInventorySystemComponent;
struct FItemInfomation;

class RPG01_API IInventoryInterface
{
	GENERATED_BODY()

public:

	virtual UInventorySystemComponent* GetInventorySystem() = 0;
	virtual void AddAttachedItem(int EquipmentIndex, FItemInfomation& ItemInfo) = 0;
	virtual void RemoveAttachedItem(int EquipmentIndex, FItemInfomation& ItemInfo, bool bChangeCurrentStats) = 0;

};
