// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/Enemy.h"

#include "UI/EnemyHealthBarComponent.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorld;

	EnemyHealthBar = CreateDefaultSubobject<UEnemyHealthBarComponent>(FName("HealthBar"));
	EnemyHealthBar->SetupAttachment(GetRootComponent());
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyHealthBar)
	{
		EnemyHealthBar->SetHealthPercent(0.1F);
	}
}

void AEnemy::ShowHealthBar(bool bShowHealth)
{
	if (EnemyHealthBar)
	{
		EnemyHealthBar->SetVisibility(bShowHealth);
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
