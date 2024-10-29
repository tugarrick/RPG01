// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StatComponent.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	BaseStats.Emplace(EStat::Health, 0.0f);
	BaseStats.Emplace(EStat::Stamina, 0.0f);
	BaseStats.Emplace(EStat::Mana, 0.0f);
	BaseStats.Emplace(EStat::Armor, 0.0f);
	BaseStats.Emplace(EStat::PhysicalDamage, 0.0f);
	BaseStats.Emplace(EStat::MagicalDamage, 0.0f);
	BaseStats.Emplace(EStat::MovementSpeed, 0.0f);
	BaseStats.Emplace(EStat::AttackSpeed, 0.0f);
	BaseStats.Emplace(EStat::Cooldown, 0.0f);

	Stats.Emplace(EStat::Health, FStatInfo());
	Stats.Emplace(EStat::Stamina, FStatInfo());
	Stats.Emplace(EStat::Mana, FStatInfo());
	Stats.Emplace(EStat::Armor, FStatInfo());
	Stats.Emplace(EStat::PhysicalDamage, FStatInfo());
	Stats.Emplace(EStat::MagicalDamage, FStatInfo());
	Stats.Emplace(EStat::MovementSpeed, FStatInfo());
	Stats.Emplace(EStat::AttackSpeed, FStatInfo());
	Stats.Emplace(EStat::Cooldown, FStatInfo());

}

// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupStats();
}

float UStatComponent::GetCurrentStat(const EStat& Stat)
{
	return Stats.Find(Stat)->CurrentStat;
}

float UStatComponent::GetMaxStat(const EStat& Stat)
{
	return Stats.Find(Stat)->MaxStat;
}

float UStatComponent::GetBaseStat(const EStat& Stat)
{
	return *BaseStats.Find(Stat);
}

void UStatComponent::SetCurrentStat(const EStat& Stat, float NewCurrentStat)
{
	auto StatInfo = Stats.Find(Stat);
	StatInfo->CurrentStat = FMath::Clamp(NewCurrentStat, 0.0f, StatInfo->MaxStat);
}

void UStatComponent::SetMaxStat(const EStat& Stat, float NewMaxStat, bool bChangeCurrentStat)
{
	auto StatInfo = Stats.Find(Stat);
	StatInfo->MaxStat = FMath::Max(NewMaxStat, 0.0f);

	if (bChangeCurrentStat)
	{
		StatInfo->CurrentStat = FMath::Min(StatInfo->CurrentStat, StatInfo->MaxStat);
	}
}

void UStatComponent::SetBaseStat(const EStat& Stat, float NewBaseStat)
{
	*BaseStats.Find(Stat) = NewBaseStat;
}

void UStatComponent::SetupStats()
{
	Stats.Find(EStat::Health)->CurrentStat = *BaseStats.Find(EStat::Health);
	Stats.Find(EStat::Health)->MaxStat = *BaseStats.Find(EStat::Health);

	Stats.Find(EStat::Stamina)->CurrentStat = *BaseStats.Find(EStat::Stamina);
	Stats.Find(EStat::Stamina)->MaxStat = *BaseStats.Find(EStat::Stamina);

	Stats.Find(EStat::Mana)->CurrentStat = *BaseStats.Find(EStat::Mana);
	Stats.Find(EStat::Mana)->MaxStat = *BaseStats.Find(EStat::Mana);

	Stats.Find(EStat::Armor)->CurrentStat = *BaseStats.Find(EStat::Armor);
	Stats.Find(EStat::Armor)->MaxStat = *BaseStats.Find(EStat::Armor);

	Stats.Find(EStat::PhysicalDamage)->CurrentStat = *BaseStats.Find(EStat::PhysicalDamage);
	Stats.Find(EStat::PhysicalDamage)->MaxStat = *BaseStats.Find(EStat::PhysicalDamage);

	Stats.Find(EStat::MagicalDamage)->CurrentStat = *BaseStats.Find(EStat::MagicalDamage);
	Stats.Find(EStat::MagicalDamage)->MaxStat = *BaseStats.Find(EStat::MagicalDamage);

	Stats.Find(EStat::MovementSpeed)->CurrentStat = *BaseStats.Find(EStat::MovementSpeed);
	Stats.Find(EStat::MovementSpeed)->MaxStat = *BaseStats.Find(EStat::MovementSpeed);

	Stats.Find(EStat::AttackSpeed)->CurrentStat = *BaseStats.Find(EStat::AttackSpeed);
	Stats.Find(EStat::AttackSpeed)->MaxStat = *BaseStats.Find(EStat::AttackSpeed);

	Stats.Find(EStat::Cooldown)->MaxStat = *BaseStats.Find(EStat::Cooldown);
}

void UStatComponent::AddExperience(float ExpAmount)
{
	CurrentExp += ExpAmount;
	if (CurrentExp >= RequiredExp)
	{
		CurrentExp -= RequiredExp;
		LevelUp();
	}
}

void UStatComponent::LevelUp()
{
	Level += 1;
	*BaseStats.Find(EStat::Health) *= 1.1f;
	*BaseStats.Find(EStat::Stamina) *= 1.1f;
	*BaseStats.Find(EStat::Mana) *= 1.1f;
	*BaseStats.Find(EStat::Armor) *= 1.1f;
	*BaseStats.Find(EStat::PhysicalDamage) *= 1.1f;
	*BaseStats.Find(EStat::MagicalDamage) *= 1.1f;
	*BaseStats.Find(EStat::AttackSpeed) += 0.05f;

	RequiredExp *= 1.5f;
}



