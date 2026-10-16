// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "UseItemBase.h"

#include "InventoryData.generated.h"

class AItemPickUpBase;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None, // Empty Handed
	Equipment,
	KeyItem,
	Collectible,
	Other
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	FString ItemDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	TSoftClassPtr<UUseItemBase> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	TSoftClassPtr<AItemPickUpBase> ItemPickUpClass;
};

USTRUCT(BlueprintType)
struct FItemReferenceMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	TMap<EItemType, FInventoryItem> ItemMap;
};

UCLASS()
class HAUNTEDPYRAMID_API UInventoryData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UInventoryData();
};
