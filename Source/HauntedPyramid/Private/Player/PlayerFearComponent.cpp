// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerFearComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UPlayerFearComponent::UPlayerFearComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	FearWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("FearWidgetComponent"));
	FearWidgetComponent->SetupAttachment(this);
	FearWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	FearWidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f));

	// ...
}


// Called when the game starts
void UPlayerFearComponent::BeginPlay()
{
	Super::BeginPlay();

	if (FearWidgetClass)
	{
		FearWidgetComponent->SetWidgetClass(FearWidgetClass);
		FearWidgetComponent->InitWidget();
	}

}


// Called every frame
void UPlayerFearComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerFearComponent::CurrentFearLevel(float& OutFearLevel) const
{
	OutFearLevel = FearLevel;
}

void UPlayerFearComponent::IncreaseFear(float Amount)
{
	FearLevel += Amount;


}

void UPlayerFearComponent::DecreaseFear(float Amount)
{
	FearLevel -= Amount;
}

void UPlayerFearComponent::SetWidgetFearLevel(float NewFearLevel)
{

}

