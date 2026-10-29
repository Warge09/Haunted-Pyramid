// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Environment/CleanableObject.h"
#include "EquipmentAnimationInterface.h"

#include "BrushEquipment.generated.h"

UCLASS()
class HAUNTEDPYRAMID_API ABrushEquipment : public AActor, public IEquipmentAnimationInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrushEquipment();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brush")
	float BrushSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brush")
	float BrushSize = 1.0f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LineTraceTargetCheck();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Trace")
	float TraceDistance = 200.0f; // Distance that the line trace will check for targets

	UPROPERTY(EditAnywhere, Category = "Brush")
	bool bIsBrushing = false; // Whether the brush is currently being used

	virtual void PlayEquipmentAnimationImplement();
	virtual void PlayUnEquipAnimationImplement();
	virtual void PlayUseAnimationInmplement();
	virtual void PlayUnUseAnimationImplement();
};
