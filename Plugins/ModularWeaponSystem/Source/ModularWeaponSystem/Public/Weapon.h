// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Weapon.generated.h"

class UWeaponDataAsset;

UCLASS()
class MODULARWEAPONSYSTEM_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();
	
	UPROPERTY(EditDefaultsOnly)
	UWeaponDataAsset* WeaponData;

	// UPROPERTY(Instanced, EditDefaultsOnly)
	//UFireModeComponent* FireMode;UFUNCTION(BlueprintCallable, Category = Weapon)
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void Initialize(UWeaponDataAsset* InWeaponData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
