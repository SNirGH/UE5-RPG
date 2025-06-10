// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Component/AttributesComponent.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Attributes = CreateDefaultSubobject<UAttributesComponent>(FName("Attributes"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::PlayAttackMontage()
{
	PlayRandomSectionInMontage(AttackMontage);
}

float ABaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	
	return DamageAmount;
}

void ABaseCharacter::HandleDamage(float DamageAmount)
{
	if (Attributes)
	{
		Attributes->RecieveDamage(DamageAmount);
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::PlayMontageSection(UAnimMontage* Montage, FName SectionName)
{
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(SectionName, Montage);
	}
}

void ABaseCharacter::PlayRandomSectionInMontage(UAnimMontage* Montage)
{
	if (!Montage) return;
	
	TArray<FName> SectionNames = GetAllMontageSectionNames(Montage);
	const int32 MaxSectionIndex = SectionNames.Num() - 1;
	const int32 SectionIndex = FMath::RandRange(0, MaxSectionIndex);
	
	PlayMontageSection(Montage, SectionNames[SectionIndex]);
}

TArray<FName> ABaseCharacter::GetAllMontageSectionNames(UAnimMontage* Montage)
{
	if (!Montage) return TArray<FName>();

	if (MontageSectionNames.Contains(Montage))
	{
		return MontageSectionNames[Montage];
	}
	
	TArray<FName> Sections;
	for (const FCompositeSection& Section : Montage->CompositeSections)
	{
		Sections.AddUnique(Section.SectionName);
	}

	MontageSectionNames.Add(Montage, Sections);
	return Sections;
}
