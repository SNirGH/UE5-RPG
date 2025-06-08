// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Characters/States/CharacterTypes.h"
#include "PlayerCharacter.generated.h"

class AItemBase;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class RPG_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	/** Virtual Functions **/
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

	/** Non-Virtual Functions **/
	void SetOverlappingItem(AItemBase* OverlappingItem);

	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
protected:
	/** Virtual Functions **/
	virtual void BeginPlay() override;
	virtual void AttackEnd() override;
	
	virtual bool CanAttack() override;
	
	/** Non-Virtual Functions**/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Pickup(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);

	bool IsUnOccupied() const;


	/** Input Mapping Context & Input Actions **/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> PlayerInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> PickupAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> SprintAction;

	/** Components **/
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	/** Movement Speeds **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Speed")
	float WalkSpeed = 300.0F;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Speed")
	float RunSpeed = 600.0F;

private:
	/** Non-Virtual Functions **/
	void EquipWeapon();
	void UsePotion();
	
	/** Overlapping Item **/
	UPROPERTY(VisibleinstanceOnly)
	TObjectPtr<AItemBase> OverlappingItem;

	/** Character Types **/
	UPROPERTY(VisibleAnywhere, Category = States)
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	
	UPROPERTY(VisibleAnywhere, Category = States)
	EActionState ActionState = EActionState::EAS_Unoccupied;
};
