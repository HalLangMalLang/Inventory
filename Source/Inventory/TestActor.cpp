// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	TMap<int32, FString> MapA = { {1,TEXT("감자")},{2,TEXT("고구마")}, {3,TEXT("호박")} };

	// 맵에 몇 개의 요소가 들어있는지 개수를 반환하는 함수
	int32 Num = MapA.Num();
	UE_LOG(LogTemp, Log, TEXT("MapA의 요소 개수 : %d"), Num);

	// GenerateValueArray(TArray<ValueType>& OutArray) : 맵의 모든 Value을 TArray로 복사하는 함수
	TArray<FString> MapAValues;
	MapA.GenerateValueArray(MapAValues);

	// GenerateValueArray(TArray<ValueType>& OutArray) : 맵의 모든 Key를 TArray로 복사하는 함수
	TArray<int32> MapAKeys;
	MapA.GenerateKeyArray(MapAKeys);

}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

