// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyHealthBarComponent.h"

#include "Components/ProgressBar.h"
#include "UI/EnemyHealthBarWidget.h"

void UEnemyHealthBarComponent::SetHealthPercent(float Percent)
{
	if (!EnemyHealthBar)
	{
		EnemyHealthBar = Cast<UEnemyHealthBarWidget>(GetUserWidgetObject());
	}

	if (EnemyHealthBar->HealthBar)
	{
		EnemyHealthBar->HealthBar->SetPercent(Percent);
	}
}
