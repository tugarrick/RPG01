// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/InventorySystemData.h"

UTexture* UInventorySystemData::GetStatTypeBGIcon(const EStat& StatType)
{
	if (StatTypeBGIcons.IsValidIndex(int(StatType)))
	{
		return StatTypeBGIcons[int(StatType)];
	}
	return nullptr;
}

UTexture* UInventorySystemData::GetItemTypeBGIcon(int EquipmentIndex)
{
	if (ItemTypeBGIcons.IsValidIndex(EquipmentIndex))
	{
		return ItemTypeBGIcons[EquipmentIndex];
	}
	return nullptr;
}
