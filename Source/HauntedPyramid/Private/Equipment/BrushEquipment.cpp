// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BrushEquipment.h"

// Sets default values
ABrushEquipment::ABrushEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

}

// Called when the game starts or when spawned
void ABrushEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABrushEquipment::LineTraceTargetCheck()
{

	if (!bIsBrushing) return;

	FHitResult OutHitResult;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + (GetActorForwardVector() * TraceDistance);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignore the actor itself

	GetWorld()->LineTraceSingleByChannel(OutHitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
	
	// Check if the hit result is valid and the hit actor has the "Pickup" tag
	if (OutHitResult.bBlockingHit && IsValid(OutHitResult.GetActor()) && OutHitResult.GetActor()->Tags.Contains(FName("Pickup")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *OutHitResult.GetActor()->GetName());
		DrawDebugLine(GetWorld(), TraceStart, OutHitResult.ImpactPoint, FColor::Green, false, 5.0f, 0, 10.0f);

		// Find the UCleanableObject component on the hit actor
		UCleanableObject* CleanableComponent = OutHitResult.GetActor()->FindComponentByClass<UCleanableObject>();

		if (CleanableComponent)
		{
			// CleanableComponent->BrushAtLocation(OutHitResult.ImpactPoint, BrushSize, BrushSpeed);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit actor does not have a UCleanableObject component."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid hit or hit actor does not have the 'Pickup' tag."));
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 5.0f, 0, 10.0f);
	}
}



// Called every frame
void ABrushEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LineTraceTargetCheck();

}

// Not used for anything but needed to avoid unresolved external symbols linker error
void ABrushEquipment::PlayEquipmentAnimationImplement()
{

}

void ABrushEquipment::PlayUnEquipAnimationImplement()
{

}

void ABrushEquipment::PlayUseAnimationImmplement()
{

}

void ABrushEquipment::PlayStopUsingAnimationImplement()
{

}


