// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/AI/BTTask_RandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UBTTask_RandomLocation::UBTTask_RandomLocation()
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type UBTTask_RandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	const ACharacter* AICharacter = AIController->GetCharacter();
	if (!AICharacter) return EBTNodeResult::Failed;

	const FVector ActorLocation = AICharacter->GetActorLocation();
	const UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavigationSystem) return EBTNodeResult::Failed;

	if (FNavLocation ResultLocation; NavigationSystem->GetRandomReachablePointInRadius(ActorLocation, SearchRadius, ResultLocation))
	{
		UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
		BlackboardComponent->SetValueAsVector(Location.SelectedKeyName, FVector(ResultLocation.Location.X, ResultLocation.Location.Y, ActorLocation.Z));

		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
