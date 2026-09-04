// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "ReloadComponent.generated.h"

class AWeapon;

UCLASS(Abstract)
class MODULARWEAPONSYSTEM_API UReloadComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	virtual bool CanReload(AWeapon* OwningWeapon) { return false; }
	virtual bool TryReload(AWeapon* OwningWeapon) { return false; }
	virtual void ConsumeAmmo(int Amount) { }
	virtual bool HasAmmo() { return false; }
};

UCLASS()
class MODULARWEAPONSYSTEM_API UMagazineComponent : public UReloadComponent
{
	GENERATED_BODY()
	
public:
	virtual bool CanReload(AWeapon* OwningWeapon) override final;
	virtual bool TryReload(AWeapon* OwningWeapon) override final;
	virtual void ConsumeAmmo(int Amount = 1) override final;
	virtual bool HasAmmo() override final { return CurrentAmmo > 0; };
	
private:
	int CurrentAmmo = 0;
	int CurrentMagazine = 1;
	bool IsReloading = false;
};

