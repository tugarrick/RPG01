// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items.generated.h"

UCLASS()
class RPG01_API AItems : public AActor
{
	GENERATED_BODY()
	
public:		
	AItems();	
	//virtual void Tick(float DeltaTime) override;

protected:
	
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};
