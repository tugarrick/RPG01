// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Items.h"
#include "Enum/ItemType.h"
#include "Enum/Rarity.h"
#include "Engine/DataTable.h"
#include "Enum/Stat.h"
#include "ItemInfomation.generated.h"

USTRUCT(BlueprintType)
struct RPG01_API FItemInfomation : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItems> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stack = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxStack = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelRequest = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStat, float> Stats;

	FItemInfomation();
	~FItemInfomation();
};
