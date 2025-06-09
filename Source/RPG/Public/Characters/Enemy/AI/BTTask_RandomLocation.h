// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UBTTask_RandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RandomLocation();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = Variables, meta = (ToolTip = "Random Location Within The Nav Mesh"))
	FBlackboardKeySelector Location;

	UPROPERTY(EditAnywhere, Category = Variables, meta = (ToolTip = "Searchable Radius Within The Nav Mesh"))
	float SearchRadius = 2500.0F;
};
