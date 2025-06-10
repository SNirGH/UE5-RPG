// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UAttributesComponent;
class AWeapon;

UCLASS()
class RPG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;
	
	FORCEINLINE AWeapon* GetEquippedWeapon() const { return EquippedWeapon; }
protected:

	/** Virtual Functions **/
	virtual void BeginPlay() override;
	
	virtual void PlayAttackMontage();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual bool CanAttack() { return false; }

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd() {} 

	/** Non-Virtual Functions **/
	void HandleDamage(float DamageAmount);

	/** Variables **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	TObjectPtr<AWeapon> EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Montages)
	TObjectPtr<UAnimMontage> AttackMontage;

private:
	void PlayMontageSection(UAnimMontage* Montage, FName SectionName);
	void PlayRandomSectionInMontage(UAnimMontage* Montage);
	
	TArray<FName> GetAllMontageSectionNames(UAnimMontage* Montage);
	
	TMap<const TObjectPtr<UAnimMontage>, TArray<FName>> MontageSectionNames;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributesComponent> Attributes;
};
