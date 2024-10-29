// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enum/Rarity.h"
#include "RarityData.generated.h"


UCLASS()
class RPG01_API URarityData : public UDataAsset
{
	GENERATED_BODY()
public:

	FColor GetRarityColor(const ERarity& Rarity);
	UTexture* GetRarityBGIcon(const ERarity& Rarity);
	UTexture* GetRarityBGIcon_2(const ERarity& Rarity);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Rarity")
	TArray<TObjectPtr<UTexture>> BGIcons;

	UPROPERTY(EditDefaultsOnly, Category = "Rarity")
	TArray<TObjectPtr<UTexture>> BGIcons_2;

	UPROPERTY(EditDefaultsOnly, Category = "Rarity")
	TArray<FColor> Colors;
};
