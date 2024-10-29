// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/RarityData.h"

FColor URarityData::GetRarityColor(const ERarity& Rarity)
{
	if (Colors.IsValidIndex(int(Rarity)))
	{
		return Colors[int(Rarity)];
	}
	return FColor();
}

UTexture* URarityData::GetRarityBGIcon(const ERarity& Rarity)
{
	if (BGIcons.IsValidIndex(int(Rarity)))
	{
		return BGIcons[int(Rarity)];
	}
	return nullptr;
}

UTexture* URarityData::GetRarityBGIcon_2(const ERarity& Rarity)
{
	if (BGIcons_2.IsValidIndex(int(Rarity)))
	{
		return BGIcons_2[int(Rarity)];
	}
	return nullptr;
}
