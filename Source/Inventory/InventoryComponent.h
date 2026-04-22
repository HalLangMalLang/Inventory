// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "ItemInfoWidget.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> InventoryWidgetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> InventorySlotWidgetClass = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	UUserWidget* InventoryWidgetInstance = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> ItemInfoWidgetClass = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	UItemInfoWidget* ItemInfoWidgetInstance = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	class UWrapBox* InventoryWrapBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxInventoryCapacity = 10;	
 
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// 인벤토리 활성화/비활성화(Toggle)
	UFUNCTION(BlueprintCallable)
	void InventoryToggle(APlayerController* PlayerController, bool Active); 

	// 인벤토리 슬롯 업데이트(Slot Update)
	UFUNCTION(BlueprintCallable)
	bool LoadInventory(APlayerController* PlayerController);

	// 인벤토리에 ItemKey에 해당하는 아이템 추가
	UFUNCTION(BlueprintCallable)
	void AddItem(APlayerController* PlayerController, int32 ItemKey, int32 Count);

	UFUNCTION(BlueprintCallable)
	void ItemClickHandle(int32 ItemKey);

private:
	// key : 아이템의 ItemKey , Value : 배열의 Index , ItemKey로 빠르게 접근하기위한 컨테이너
	TMap<int32, int32> InventoryMap;

	// 아이템을 저장할 배열
	TArray<TPair<FInventorySlotData, class UInventorySlotWidget*>> Inventory;
};
