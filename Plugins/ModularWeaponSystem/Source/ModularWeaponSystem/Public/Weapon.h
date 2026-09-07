// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Weapon.generated.h"

class UWeaponDataAsset;
class UReloadComponent;
class UWeaponActionComponent;
class UWeaponCollisionComponent;

UCLASS(BlueprintType, BlueprintType)
class MODULARWEAPONSYSTEM_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly)
	UWeaponDataAsset* WeaponData;
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void Initialize(UWeaponDataAsset* InWeaponData);
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void OnActionPressed();
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void OnActionReleased();
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void OnActionHeld(float dt);
	
	UReloadComponent* GetReloadComponent() const { return ReloadComponent; }
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	UWeaponCollisionComponent* GetCollisionComponent() const { return CollisionComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UReloadComponent* ReloadComponent = nullptr;
	UWeaponActionComponent* ActionComponent = nullptr;
	UWeaponCollisionComponent* CollisionComponent = nullptr;
};
