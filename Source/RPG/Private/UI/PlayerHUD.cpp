// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHUD::SetHealthBar(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void UPlayerHUD::SetStaminaBar(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

void UPlayerHUD::SetGoldText(int32 Gold)
{
	if (GoldText)
	{
		GoldText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Gold)));
	}
}

void UPlayerHUD::SetSoulsText(int32 Souls)
{
	if (SoulsText)
	{
		GoldText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Souls)));
	}
}
