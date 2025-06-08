// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/WeaponTrailActivation.h"

#include "Characters/Player/PlayerCharacter.h"
#include "Items/Weapons/Weapon.h"

void UWeaponTrailActivation::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp) return;

	PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (PlayerCharacter)
	{
		Weapon = PlayerCharacter->GetEquippedWeapon();
		if (Weapon)
		{
			Weapon->ActivateWeaponTrail();
		}
	}
}

void UWeaponTrailActivation::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp) return;

	if (Weapon)
	{
		Weapon->DeactivateWeaponTrail();
	}
}
