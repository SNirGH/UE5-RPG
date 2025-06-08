// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/ItemBase.h"
#include "Items/Weapons/Weapon.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	/** Disable Use Control Rotation **/
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	/** Spring Arm Settings **/
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 300.0F;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetupAttachment(GetRootComponent());

	/** Camera Settings **/
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	/** Character Movement Settings **/
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerInputMappingContext, 0);
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Started, this, &APlayerCharacter::Pickup);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerCharacter::Attack);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopSprint);
	}
}

void APlayerCharacter::Jump()
{
	if (IsUnOccupied())
	{
		Super::Jump();
	}
}

void APlayerCharacter::SetOverlappingItem(AItemBase* Item)
{
	OverlappingItem = Item;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0F, Rotation.Yaw, 0.0F);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookRotation = Value.Get<FVector2D>();

	AddControllerYawInput(LookRotation.X);
	AddControllerPitchInput(LookRotation.Y);
}

void APlayerCharacter::Pickup(const FInputActionValue& Value)
{
	if (!OverlappingItem) return;

	switch (OverlappingItem->GetItemType())
	{
	case EItemType::EIT_Weapon:
		EquipWeapon();
		break;
	case EItemType::EIT_Potion:
		UsePotion();
		break;
	default:
		break;
	}
}

void APlayerCharacter::Attack(const FInputActionValue& Value)
{
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void APlayerCharacter::Sprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void APlayerCharacter::StopSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

bool APlayerCharacter::IsUnOccupied() const
{
	return ActionState == EActionState::EAS_Unoccupied;
}

bool APlayerCharacter::CanAttack()
{
	return CharacterState != ECharacterState::ECS_Unequipped &&
		ActionState == EActionState::EAS_Unoccupied &&
		!GetCharacterMovement()->IsFalling();
}

void APlayerCharacter::AttackEnd()
{
	Super::AttackEnd();

	ActionState = EActionState::EAS_Unoccupied;
}


void APlayerCharacter::EquipWeapon()
{
	if (!OverlappingItem) return;

	if (AWeapon* Weapon = Cast<AWeapon>(OverlappingItem))
	{
		Weapon->Equip(GetMesh(), FName("WeaponSocket"), this, this);
		CharacterState = ECharacterState::ECS_Equipped;
		OverlappingItem = nullptr;
		EquippedWeapon = Weapon;
	}
}

void APlayerCharacter::UsePotion()
{
	if (!OverlappingItem) return;

	OverlappingItem->Destroy();
	OverlappingItem = nullptr;
}

