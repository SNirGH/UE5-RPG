// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AWeapon::AWeapon()
{
	ItemType = EItemType::EIT_Weapon;
}

void AWeapon::AttachWeaponToSocket(USceneComponent* InParent, const FName& SocketName)
{
	const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, TransformRules, SocketName);
}

void AWeapon::Equip(USceneComponent* InParent, const FName& SocketName, AActor* NewOwner, APawn* NewInstigator)
{
	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	
	AttachWeaponToSocket(InParent, SocketName);
	ItemOverlap->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemState = EItemState::EIS_Equipped;
	// TODO: Play Sound Effect
}

void AWeapon::WeaponTrace()
{
	const FVector TraceStart = ItemMesh->GetSocketLocation(TEXT("WeaponStart"));
	const FVector TraceEnd = ItemMesh->GetSocketLocation(TEXT("WeaponEnd"));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());

	FHitResult BoxHit;

	for (AActor* Actor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
	}
	
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		TraceStart,
		TraceEnd,
		BoxTraceExtent,
		GetActorRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		bShowBoxDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		BoxHit,
		true
	);
	IgnoreActors.AddUnique(BoxHit.GetActor());
}

void AWeapon::ActivateWeaponTrail()
{
	if (!TrailSystem) return;
	
	const FVector TrailStart = ItemMesh->GetSocketLocation(FName("WeaponStart"));
	const FVector TrailEnd = ItemMesh->GetSocketLocation(FName("WeaponEnd"));

	const FVector TrailLocation = (TrailStart + TrailEnd) / 2.0F;
	const FVector Direction = (TrailEnd - TrailStart).GetSafeNormal();
	const FRotator TrailRotation = FRotationMatrix::MakeFromZ(Direction).Rotator();

	TrailComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
		TrailSystem,
		ItemMesh,
		NAME_None,
		TrailLocation,
		TrailRotation,
		EAttachLocation::KeepWorldPosition,
		false,
		true
	);

	if (TrailComponent)
	{
		const float RibbonWidth = (TrailEnd - TrailStart).Length();
		TrailComponent->SetFloatParameter(FName("User.RibbonWidth"), RibbonWidth);
	}
}

void AWeapon::DeactivateWeaponTrail()
{
	if (TrailComponent)
	{
		TrailComponent->Deactivate();
		TrailComponent = nullptr;
	}
}

