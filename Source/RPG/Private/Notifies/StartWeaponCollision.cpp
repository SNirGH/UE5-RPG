// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/StartWeaponCollision.h"

#include "Characters/Player/PlayerCharacter.h"
#include "Items/Weapons/Weapon.h"

void UStartWeaponCollision::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner()))
	{
		if (AWeapon* Weapon = PlayerCharacter->GetEquippedWeapon())
		{
			Weapon->WeaponTrace();
		}
	}
}
