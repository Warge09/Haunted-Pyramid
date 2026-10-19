// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/CleanableObject.h"
#include "Components/StaticMeshComponent.h"
#include "StaticMeshResources.h"
#include "StaticMeshComponentLODInfo.h"
#include "Rendering/PositionVertexBuffer.h"


// Sets default values for this component's properties
UCleanableObject::UCleanableObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCleanableObject::BeginPlay()
{
	Super::BeginPlay();


}


void UCleanableObject::BrushAtLocation(FVector HitLocation, float BrushRadius, float CleanSpeed)
{


}



// Called every frame
void UCleanableObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



