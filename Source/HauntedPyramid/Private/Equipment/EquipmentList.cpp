// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/EquipmentList.h"

// Sets default values for this component's properties
UEquipmentList::UEquipmentList()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UEquipmentList::AddEquipmentItem(TSubclassOf<AActor> ItemClass)
{
	for (TSubclassOf<AActor> Item : EquipmentItems)
	{

		if (Item == ItemClass)
		{
			//UE_LOG(EquipmentWarning, Warning, TEXT("Item %s is already in the equipment list."), *ItemClass->GetName());
			return;
		}
	}
}

void UEquipmentList::GetEquippedItems(TArray<AActor*>& OutEquippedItems) const
{


}

void UEquipmentList::EquipItem(TSubclassOf<AActor> ItemClass)
{


}


// Called when the game starts
void UEquipmentList::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipmentList::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

