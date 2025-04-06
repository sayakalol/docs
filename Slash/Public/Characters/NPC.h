// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

class UBoxComponent;
class USphereComponent;
class ASlashCharacter;
class UWidgetComponent;
class UShopSystemComponent;

UCLASS()
class SLASH_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	ASlashCharacter* OverlappingCharacter; // 当前重叠的角色


	UPROPERTY(BlueprintReadWrite)
	bool IsShowWidget = false;

private:

	/*UPROPERTY(VisibleAnywhere, blueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UShopSystemComponent* ShopSystem;*/

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* NameWidget;


	UFUNCTION(BlueprintCallable)
	void OpenStoreUI();

	FORCEINLINE ASlashCharacter* GetOverlappingCharacter() const { return OverlappingCharacter; }
	FORCEINLINE void SetIsShowWidget(bool bShow) { IsShowWidget = bShow; }
};
