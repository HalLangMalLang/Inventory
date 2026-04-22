// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGameInstance.h"

UInventoryGameInstance::UInventoryGameInstance() : ItemDataTable(nullptr) {}

FItemData* UInventoryGameInstance::FindItem(int32 ItemKey) const
{
	if (ItemDataTable)
	{
		const TMap<FName, uint8*>& RowMap = ItemDataTable->GetRowMap();
		for (const auto& RowPair : RowMap)
		{
			FItemData* ItemData = reinterpret_cast<FItemData*>(RowPair.Value);

			if (ItemData && ItemData->ItemKey == ItemKey)
			{
				return ItemData;
			}
		}
	}

	return nullptr;
}
