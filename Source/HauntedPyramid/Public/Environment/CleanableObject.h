// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Components/ActorComponent.h"
#include "CleanableObject.generated.h"


// Use this delegate to notify when the object has been fully cleaned
// This will be used to trigger events such as audio, interaction UI, animation, etc
UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObjectFinishedCleaning);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HAUNTEDPYRAMID_API UCleanableObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCleanableObject();

	UFUNCTION(BlueprintCallable, Category = "Cleanable Object")
	void BrushAtLocation (FVector HitLocation, float BrushRadius, float CleanSpeed);

	UPROPERTY(BlueprintAssignable, Category = "Cleanable Object")
	FOnObjectFinishedCleaning OnObjectFinishedCleaning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cleanable Object")
	bool BIsCleaned = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cleanable Object", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float CleanedPercentage = 0.75f; // Percentage of the object that needs to  been cleaned, from 0.0 (completely dirty) to 1.0 (completely clean)



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: 
	

};
