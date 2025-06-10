// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "Weapon.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class RPG_API AWeapon : public AItemBase
{
	GENERATED_BODY()

public:
	AWeapon();

	void AttachWeaponToSocket(USceneComponent* InParent, const FName& SocketName);
	void Equip(USceneComponent* InParent, const FName& SocketName, AActor* NewOwner, APawn* NewInstigator);
	void WeaponTrace();
	void ActivateWeaponTrail();
	void DeactivateWeaponTrail();

	TArray<TObjectPtr<AActor>> IgnoreActors;

protected:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	FVector BoxTraceExtent = FVector(5.F);

	UPROPERTY(EditAnywhere, Category = "Weapons Properties")
	bool bShowBoxDebug = false;

	UPROPERTY(EditAnywhere, Category = "Weapons Properties")
	float BaseDamage = 20.0F;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effects)
	TObjectPtr<UNiagaraSystem> TrailSystem;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> TrailComponent;

};
