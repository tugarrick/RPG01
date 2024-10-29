// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/Stat.h"
#include "Struct/StatInfo.h"
#include "StatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG01_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

	float GetCurrentStat(const EStat& Stat);
	float GetMaxStat(const EStat& Stat);
	float GetBaseStat(const EStat& Stat);

	void SetCurrentStat(const EStat& Stat, float NewCurrentStat);
	void SetMaxStat(const EStat& Stat, float NewMaxStat, bool bChangeCurrentStat);
	void SetBaseStat(const EStat& Stat, float NewBaseStat);

	void SetupStats();

	void AddExperience(float ExpAmount);
	void LevelUp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStat, float> BaseStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStat, FStatInfo> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentExp = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RequiredExp = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level = 1;

};
