// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "Particles/ParticleSystem.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Flashlight.generated.h"

UCLASS()
class HAUNTEDPYRAMID_API AFlashlight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlashlight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	UStaticMeshComponent* FlashlightMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	USpotLightComponent* SpotLightComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	//UParticleSystem* FlashlightBeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight Values", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FlickerChance = 0.10f; // 0.10 10% chance of flickering

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight Values")
	float FlickerIntensity = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight Values")
	float FlickerFrequency = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight Values")
	float FlickerDuration = 5.0f; // The flicker will last for x amount of seconds 

	UFUNCTION(BlueprintCallable, Category = "Flashlight")
	void ToggleFlashlight();

	UFUNCTION(BlueprintCallable, Category = "Flashlight")
	void ToggleFlashlightOff();

	UFUNCTION(BlueprintCallable, Category = "Flashlight")
	void RandomFlicker();

	bool bIsOn = false;
	bool bIsFlickering = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* FlashlightSound;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
