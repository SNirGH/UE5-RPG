// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "WeaponTrailActivation.generated.h"

class AWeapon;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class RPG_API UWeaponTrailActivation : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AWeapon> Weapon;
};
