// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatInfo.generated.h"

USTRUCT(BlueprintType)
struct RPG01_API FStatInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentStat = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStat = 0.0f;

};
