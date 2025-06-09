// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/EnemyController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemyController::AEnemyController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("SightConfig"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));

	SightConfig->SightRadius = 1500.0F;
	SightConfig->LoseSightRadius = 1600.0F;
	SightConfig->PeripheralVisionAngleDegrees = 45.0F;
	SightConfig->SetMaxAge(5.0F);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	BlackboardComponent = GetBlackboardComponent();
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::OnTargetPerceptionUpdated);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetBlackboardComponent()->GetBlackboardAsset()->GetName());
	}
}

void AEnemyController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		BlackboardComponent->SetValueAsObject(FName("CombatTarget"), Actor);
	}
	else
	{
		BlackboardComponent->SetValueAsObject(FName("CombatTarget"), nullptr);
	}
}
