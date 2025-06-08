// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EnemyHealthBarComponent.generated.h"

UCLASS(ClassGroup = "User Interface", meta = (BlueprintSpawnableComponent))
class RPG_API UEnemyHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
 void SetHealthPercent(float Percent);
private:
	UPROPERTY()
	TObjectPtr<class UEnemyHealthBarWidget> EnemyHealthBar;
};
