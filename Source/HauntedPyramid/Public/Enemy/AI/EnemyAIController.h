// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class HAUNTEDPYRAMID_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

/*	UPROPERTY(VisibleAnywhere, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> EnemyPerceptionComponent; */

	UPROPERTY(VisibleAnywhere, Category = "AI")
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig;


	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);
	void OnTargetLost(AActor* Actor, FAIStimulus Stimulus);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

};
