// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PreviewTreyCharacter.generated.h"

struct FItemInfomation;

UCLASS()
class RPG01_API APreviewTreyCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APreviewTreyCharacter();
	//virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AttachItem(int EquipmentIndex, FItemInfomation& ItemInfo);
	void DetachItem(int EquipmentIndex);

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> ChestComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> HandsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> LegsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> FeetComponent;

	UPROPERTY()
	TMap<int, TObjectPtr<AActor>> AttachedActors;

};
