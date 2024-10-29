// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractPromptWidget.generated.h"

class UTextBlock;
UCLASS()
class RPG01_API UInteractPromptWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	void UpdateText(FText NewText, FColor NewColor);

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName;

	
};
