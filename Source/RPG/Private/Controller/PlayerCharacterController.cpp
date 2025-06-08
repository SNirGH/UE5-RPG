// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PlayerCharacterController.h"

#include "UI/PlayerHUD.h"

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController() && PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UPlayerHUD>(this, PlayerWidgetClass);
		if (PlayerWidget)
		{
			PlayerWidget->AddToViewport();
		}
	}
}
