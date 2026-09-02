// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerFearComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HAUNTEDPYRAMID_API UPlayerFearComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFearComponent();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Fear")
	float FearLevel = 0.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Fear")
	void CurrentFearLevel(float& OutFearLevel) const;

	UFUNCTION(BlueprintCallable, Category = "Fear")
	void IncreaseFear(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Fear")
	void DecreaseFear(float Amount);
		
};
