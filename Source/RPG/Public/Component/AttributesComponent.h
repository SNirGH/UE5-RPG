// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributesComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Attributes)
	float Health;

	UPROPERTY(EditAnywhere, Category = Attributes)
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = Attributes)
	float Stamina;

	UPROPERTY(EditAnywhere, Category = Attributes)
	float MaxStamina;

	UPROPERTY(EditAnywhere, Category = Attributes)
	int32 Gold;
};
