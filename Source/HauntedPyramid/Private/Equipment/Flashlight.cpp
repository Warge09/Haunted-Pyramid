// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Flashlight.h"
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

void AFlashlight::ToggleFlashlight()
{
	bIsOn = true;
	SpotLightComponent->SetVisibility(bIsOn);	

	RandomFlicker();

	if (FlashlightSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FlashlightSound, GetActorLocation());
	}


}

void AFlashlight::ToggleFlashlightOff()
{
	bIsOn = false;
	SpotLightComponent->SetVisibility(bIsOn);

	if (FlashlightSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FlashlightSound, GetActorLocation());
	}
}

void AFlashlight::RandomFlicker()
{

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
			else
			{
				SpotLightComponent->SetVisibility(true);
			}
			bIsFlickering = false;
		}, 2.0f, true);
	}
}

// Called when the game starts or when spawned
void AFlashlight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


