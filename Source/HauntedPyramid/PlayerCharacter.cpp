// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerFearComponent = CreateDefaultSubobject<UPlayerFearComponent>(TEXT("PlayerFearComponent"));

	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	else 	
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is not valid."));
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);


	if(!PlayerFearComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerFearComponent is not valid."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerFearComponent is valid."));
	}

}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin with %s outside of if statement"), *OtherActor->GetName());

	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap Begin with %s"), *OtherActor->GetName());
		PlayerFearComponent->FearLevel += 50.0f;
	}

}

void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End with %s outside of if statement"), *OtherActor->GetName());

	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap End with %s"), *OtherActor->GetName());
		PlayerFearComponent->FearLevel -= 50.0f;
	}

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();


	if (Controller != nullptr)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Sprint(const FInputActionValue& Value)
{
	if (bIsCrouched == true) return;
	if (!PlayerFearComponent) return;

	if(PlayerFearComponent->FearLevel >= 50 && StaminaAmount > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(SprintTimerHandle, [this]()
		{
				StaminaAmount -= StaminaDrainRate; // Decrease stamina over time
				StaminaAmount = FMath::Clamp(StaminaAmount, 0.f, 100.f); 
				GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

				UE_LOG(LogTemp, Warning, TEXT("Sprinting! Stamina: %f"), StaminaAmount);

			if (StaminaAmount <= 0)
			{
				StopSprinting();
				UE_LOG(LogTemp, Warning, TEXT("Stamina depleted! Stopping sprint."));
			}

		}, 0.15f, true);
	}

}

void APlayerCharacter::StopSprinting()
{
	GetWorld()->GetTimerManager().ClearTimer(SprintTimerHandle);
	GetCharacterMovement()->MaxWalkSpeed = 600.f; // Reset to normal speed

	GetWorld()->GetTimerManager().SetTimer(SprintTimerHandle, [this]()
		{
			if (PlayerFearComponent)
			{

				if (PlayerFearComponent->FearLevel == 0)
				{
					StaminaAmount += StaminaRecoveryRate;
					StaminaAmount = FMath::Clamp(StaminaAmount, 0.f, 100.f);

					if (StaminaAmount >= 100)
					{
						UE_LOG(LogTemp, Warning, TEXT("Stamina fully recovered!"));
					}
				}
			}

		}, 0.25f, true);
}

void APlayerCharacter::Jump()
{
	ACharacter::Jump();
}

void APlayerCharacter::StopJumping()
{
	ACharacter::StopJumping();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopSprinting);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);
	}
}
