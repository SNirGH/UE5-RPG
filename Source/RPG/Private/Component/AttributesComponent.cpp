// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AttributesComponent.h"


UAttributesComponent::UAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttributesComponent::RecieveDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.0F, MaxHealth);
}

void UAttributesComponent::UseStamina(float StaminaCost)
{
	Stamina = FMath::Clamp(Stamina - StaminaCost, 0.0F, MaxStamina);
}

void UAttributesComponent::AddGold(int32 AmountOfGold)
{
	Gold += AmountOfGold;
}

void UAttributesComponent::AddSouls(int32 AmountOfSouls)
{
	Souls += AmountOfSouls;
}

void UAttributesComponent::RegenStamina(float DeltaTime)
{
	Stamina = FMath::Clamp(Stamina + StaminaRegenRate * DeltaTime, 0.0F, MaxStamina);
}

float UAttributesComponent::GetHealthPercent()
{
	return Health / MaxHealth;
}

float UAttributesComponent::GetStaminaPercent()
{
	return Stamina / MaxStamina;
}

bool UAttributesComponent::IsAlive()
{
	return Health > 0.0F;
}

void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();
}

