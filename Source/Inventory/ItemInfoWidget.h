// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemDescriptionText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCountText;

public:
	void UpdateText(FString ItemName, FText ItemDescription, int32 ItemCount);

};
