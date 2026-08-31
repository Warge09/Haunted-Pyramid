// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Debug/DebugLogManager.h"
#include "EquipmentList.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HAUNTEDPYRAMID_API UEquipmentList : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentList();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<AActor>> EquipmentItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TArray<AActor*> EquippedItems;

	UFUNCTION(BlueprintCallable, Category = "Equipmenct")
	void AddEquipmentItem(TSubclassOf<AActor> ItemClass);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void GetEquippedItems(TArray<AActor*> &OutEquippedItems) const;	

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipItem(TSubclassOf<AActor> ItemClass);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
