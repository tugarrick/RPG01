// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enum/Stat.h"
#include "StatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG01_API IStatInterface
{
	GENERATED_BODY()

public:

	virtual float GetCurrentStat(const EStat& Stat) = 0;
	virtual float GetMaxStat(const EStat& Stat) = 0;
	virtual float GetBaseStat(const EStat& Stat) = 0;
};
