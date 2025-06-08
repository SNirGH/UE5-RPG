// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class RPG_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealthBar(float Percent);
	void SetStaminaBar(float Percent);
	void SetGoldText(int32 Gold);
	void SetSoulsText(int32 Souls);
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaProgressBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GoldText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SoulsText;
};
