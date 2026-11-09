// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/EnemyAIController.h"


AEnemyAIController::AEnemyAIController()
{
	BehaviorTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("BehaviorTree"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
//	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(PerceptionComponent))
	{
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
	}

	if (IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree.Get());
	}

}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{


}

void AEnemyAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
}

void AEnemyAIController::OnTargetLost(AActor* Actor, FAIStimulus Stimulus)
{
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

