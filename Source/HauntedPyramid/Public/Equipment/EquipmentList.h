// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "Debug/DebugLogManager.h"
#include "EquipmentList.generated.h"

class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HAUNTEDPYRAMID_API UEquipmentList : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentList();

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<AActor>> EquipmentItems; */

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void AddEquipmentItem(TSubclassOf<AActor> ItemClass);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void GetEquippedItems(TArray<AActor*> &OutEquippedItems) const;	

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipItem(int32 IndexValue);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetupInputBindings(UEnhancedInputComponent* EnhancedInputComponent, class UInputAction* InputAction);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void HandleEquipAction(const FInputActionValue& Value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TArray<TSoftObjectPtr<AActor>> EquipmentItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* EquipAction;

private: 


	int32 Index = INDEX_NONE;
	int EquipmentAmount = 0;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
