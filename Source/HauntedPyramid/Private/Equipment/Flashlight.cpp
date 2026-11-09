// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Flashlight.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFlashlight::AFlashlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	FlashlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlashlightMesh"));
	FlashlightMesh->SetupAttachment(RootComponent);

	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLightComponent->SetupAttachment(FlashlightMesh);


	SpotLightComponent->SetVisibility(false);

		// FlashlightBeam = CreateDefaultSubobject<UParticleSystem>(TEXT("FlashlightBeam"));

}

// Called when the game starts or when spawned
void AFlashlight::BeginPlay()
{
	Super::BeginPlay();

}


void AFlashlight::SetupInputBindings(UEnhancedInputComponent* EnhancedInputComponent, class UInputAction* InputAction)
{
	if (!EnhancedInputComponent || !InputAction) return;

	UE_LOG(LogTemp, Warning, TEXT("SetupInputBindings called with EnhancedInputComponent: %s and InputAction: %s"), *GetNameSafe(EnhancedInputComponent), *GetNameSafe(InputAction));

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(EnhancedInputComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent is valid."));

		if (InputAction)
		{
			UE_LOG(LogTemp, Warning, TEXT("InputAction is valid. Binding action..."));
			EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &AFlashlight::FlashlightStateCheck);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("InputAction is null."));
		}
	}

}

void AFlashlight::FlashlightStateCheck()
{
	if (bIsOn)
	{
		ToggleFlashlight();
	}
	else
	{
		ToggleFlashlightOff();
	}
}

void AFlashlight::ToggleFlashlight()
{

	bIsOn = true;
	SpotLightComponent->SetVisibility(bIsOn);	

	RandomFlicker();

	if (FlashlightSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FlashlightSound, GetActorLocation());
		FlashlightNoise();
	}


}

void AFlashlight::ToggleFlashlightOff()
{
	bIsOn = false;
	SpotLightComponent->SetVisibility(bIsOn);

	if (FlashlightSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FlashlightSound, GetActorLocation());
		FlashlightNoise();
	}
}

void AFlashlight::RandomFlicker()
{
	/*
	if (!bIsFlickering && bIsOn)
	{
		FTimerHandle FlickerCheck;
		
		GetWorld()->GetTimerManager().SetTimer(FlickerCheck, [this]()
		{
			if (FMath::FRand() < FlickerChance)
			{
				bIsFlickering = true;

				SpotLightComponent->SetVisibility(false);
				FTimerHandle FlickerTimerHandle;
				GetWorld()->GetTimerManager().SetTimer(FlickerTimerHandle, [this]()
				{
					SpotLightComponent->SetVisibility(true);
				}, FlickerDuration, false);

				UE_LOG(LogTemp, Warning, TEXT("Flashlight flickered off for %f seconds."), FlickerDuration);
			}
			bIsFlickering = false;
		}, 2.0f, true);
	}
	*/
}


// Called every frame
void AFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Not used for anything but needed to avoid unresolved external symbols linker error
void AFlashlight::PlayEquipmentAnimationImplement()
{

}

void AFlashlight::PlayUnEquipAnimationImplement()
{

}

void AFlashlight::PlayUseAnimationInmplement()
{

}

void AFlashlight::PlayStopUsingAnimationImplement()
{

}


