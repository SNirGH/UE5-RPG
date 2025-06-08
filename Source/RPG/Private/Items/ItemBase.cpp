// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

#include "Characters/Player/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetCollisionProfileName(FName("NoCollision"));
	SetRootComponent(ItemMesh);

	ItemOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("ItemOverlap"));
	ItemOverlap->SetCollisionProfileName(FName("Pickup"));
	ItemOverlap->SetupAttachment(GetRootComponent());

	ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Item Effect"));
	ItemEffect->SetupAttachment(GetRootComponent());
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	ItemOverlap->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnItemBeginOverlap);
	ItemOverlap->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnItemEndOverlap);
}

void AItemBase::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter->SetOverlappingItem(this);
	}
}

void AItemBase::OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter->SetOverlappingItem(nullptr);
	}
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ItemState == EItemState::EIS_Hovering)
	{
		RunningTime += DeltaTime;

		const float CurrentZOffset = Amplitude * FMath::Sin(RunningTime * FloatingSpeed);
		const float DeltaZ = CurrentZOffset - PreviousZOffset;
		PreviousZOffset = CurrentZOffset;
	
		const FRotator DeltaRotation = FRotator(0.F, RotationSpeed, 0.F);
	
		AddActorWorldOffset(FVector(0.F, 0.F, DeltaZ), false);
		AddActorWorldRotation(DeltaRotation * DeltaTime, false);
	}
}

