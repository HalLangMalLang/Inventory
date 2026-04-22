// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine\DataTable.h"
#include "PlayerTitle.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemKey;				// 아이템을 구분할 유일한 Key값

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString ItemName;			// 아이템 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* ItemIcon;		// 인벤토리에 보여줄 아이콘리소스

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Description;			// 아이템 정보

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EPlayerTitle RequiredTitle; // 아이템 사용 조건 -> 칭호

	FItemData() : ItemKey(-1), ItemName(TEXT("")),ItemIcon(nullptr), Description(FText::GetEmpty()), RequiredTitle(EPlayerTitle::None) {}

	FItemData(int32 InItemKey, FString InItemName, int32 InItemCount, UTexture2D* InItemIcon, FText InDescription, const EPlayerTitle& InRequiredTitle) :
		ItemKey(InItemKey), ItemName(InItemName), ItemIcon(InItemIcon), Description(InDescription), RequiredTitle(InRequiredTitle) {
	}
};


USTRUCT(BlueprintType)
struct FInventorySlotData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemCount;

	FInventorySlotData() : ItemKey(-1), ItemCount(-1) {}
};