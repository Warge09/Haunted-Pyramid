// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/EquipmentList.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UEquipmentList::UEquipmentList()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UEquipmentList::BeginPlay()
{
	Super::BeginPlay();

	if (EquipmentItems.Num() == 0) return;
	EquipmentItems.Empty();

	USkeletalMeshComponent* OwnerSkeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	const FName HandSocket = TEXT("ik_hand_gun"); // Probably a better way to do this cause of case sensitivity but oh well

	if (!OwnerSkeletalMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner does not have a SkeletalMesh"));
		return;
	}

	// Spawn and attach all equipped items to the player character, but keep them hidden and disabled until equipped.
	for(int32 i = 0; i < EquipmentClasses.Num(); i++)
	{
		TSubclassOf<AActor> ItemClasses = EquipmentClasses[i];

		if(!ItemClasses) 
		{
			continue;
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();

		// Needed so the actor's can be on top of each other in the player's hand and unhidden when needed one by one.
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector SpawnLocation = GetOwner()->GetActorLocation();
		FRotator SpawnRotation = GetOwner()->GetActorRotation();

		AActor* SpawnedItem = GetWorld()->SpawnActor<AActor>(ItemClasses, SpawnLocation, SpawnRotation, SpawnParams);

		if (SpawnedItem)
		{
			UE_LOG(LogTemp, Warning, TEXT("Items have been spawned: %s"), *SpawnedItem->GetName());
			UE_LOG(LogTemp, Warning, TEXT("Items spawned at location: X: %f, Y: %f, Z: %f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
		}
		else
		{
			continue;
		}

		SpawnedItem->AttachToComponent(OwnerSkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
		SpawnedItem->SetActorHiddenInGame(true);
		SpawnedItem->SetActorEnableCollision(false);
		SpawnedItem->SetActorTickEnabled(false);

		EquipmentItems.Add(SpawnedItem);

	}
}

void UEquipmentList::SetupInputBindings(UEnhancedInputComponent* EnhancedInputComponent, class UInputAction* InputAction)
{
	if (!EnhancedInputComponent || !InputAction) return;

	UE_LOG(LogTemp, Warning, TEXT("SetupInputBindings called with EnhancedInputComponent: %s and InputAction: %s"), *GetNameSafe(EnhancedInputComponent), *GetNameSafe(InputAction));

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(EnhancedInputComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent is valid."));

		if (InputAction)
		{	
			UE_LOG(LogTemp, Warning, TEXT("InputAction is valid. Binding action..."));
			EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &UEquipmentList::HandleEquipAction);
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("InputAction is null."));
		}
	}

}

void UEquipmentList::HandleEquipAction(const FInputActionValue& Value)
{

	const int32 NewIndex = FMath::RoundToInt(Value.Get<float>()) - 1; // Convert to 0-based index so the engine can recognise that the 1 key has been pressed.

	EquipItem(NewIndex);

	UE_LOG(LogTemp, Warning, TEXT("HandleEquipAction called with value: %f"), Value.Get<float>());

}

void UEquipmentList::GetEquippedItems(TArray<AActor*>& OutEquippedItems) const
{


}

void UEquipmentList::EquipItem(int32 IndexValue)
{
	// Cooldown between switching items so you cannot spam it.
	float CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime - LastSwapCooldownTime < SwapCooldown)
	{
		return;
	}

	LastSwapCooldownTime = CurrentTime;

	UE_LOG(LogTemp, Warning, TEXT("EquipItem called with index: %d"), IndexValue);

	if (!EquipmentItems.IsValidIndex(IndexValue)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Equipment Array Index %d"), IndexValue)
		return;
	}

	for (int32 i = 0; i < EquipmentItems.Num(); i++)
	{
		AActor* ActiveItem = EquipmentItems[i];

		if (!ActiveItem) 
		{
			continue;
		}

		const bool bShouldItemBeVisible = (i == IndexValue);

		if (bShouldItemBeVisible)
		{
			if (ActiveItem->GetClass()->ImplementsInterface(UEquipmentAnimationInterface::StaticClass()))
			{

				IEquipmentAnimationInterface::Execute_PlayEquipAnimation(ActiveItem);
			}
		}
		ActiveItem->SetActorHiddenInGame(bShouldItemBeVisible);
		ActiveItem->SetActorEnableCollision(false);
		ActiveItem->SetActorTickEnabled(bShouldItemBeVisible);
	}
}

void UEquipmentList::AddEquipmentItem(TSubclassOf<AActor> ItemClass)
{
	//for (TSubclassOf<AActor> Item : EquippedItems)
	//{



	//	if (Item == ItemClass)
	//	{
	//		//UE_LOG(EquipmentWarning, Warning, TEXT("Item %s is already in the equipment list."), *ItemClass->GetName());
	//		return;
	//	}
	//}
}

// Called every frame
void UEquipmentList::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

