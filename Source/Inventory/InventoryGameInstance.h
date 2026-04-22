// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ItemData.h"
#include "InventoryGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UInventoryGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UInventoryGameInstance();

	// 아이템의 정보가 들어있는 원본 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UDataTable* ItemDataTable;

	FItemData* FindItem(int32 ItemKey) const;
};
