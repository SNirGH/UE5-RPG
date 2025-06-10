// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Enemy.generated.h"

class UEnemyHealthBarComponent;

UCLASS()
class RPG_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;

private:
	/** Functions **/
	void ShowHealthBar(bool bShowHealth);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UEnemyHealthBarComponent> EnemyHealthBar;
};
