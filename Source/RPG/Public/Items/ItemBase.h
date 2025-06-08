// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemTypes.h"
#include "ItemBase.generated.h"

enum class EItemType : uint8;
class USphereComponent;
class UNiagaraComponent;

UCLASS()
class RPG_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE EItemType GetItemType() const { return ItemType; }
protected:
	virtual void BeginPlay() override;

	/** Functions **/
	UFUNCTION()
	virtual void OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Components **/
	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<USphereComponent> ItemOverlap;

	/** Variables **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Amplitude = 15.0F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float FloatingSpeed = 3.0F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float RotationSpeed = 45.0F;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	float PreviousZOffset = 0.0F;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FX)
	TObjectPtr<UNiagaraComponent> ItemEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Type")
	EItemType ItemType = EItemType::EIT_None;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Type")
	EItemState ItemState = EItemState::EIS_Hovering;

private:
	double RunningTime;
};
