// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryData.h"

#include "ItemPickUpBase.generated.h"

class UInventoryData;

UCLASS()
class HAUNTEDPYRAMID_API AItemPickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickUpBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
	FInventoryItem ItemData;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
