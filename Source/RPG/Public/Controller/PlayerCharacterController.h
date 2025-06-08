// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

class UPlayerHUD;
/**
 * 
 */
UCLASS()
class RPG_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	FORCEINLINE UPlayerHUD* GetPlayerHUD() const { return PlayerWidget; }
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "User Interface")
	TSubclassOf<UPlayerHUD> PlayerWidgetClass;

	UPROPERTY()
	TObjectPtr<UPlayerHUD> PlayerWidget;
};
