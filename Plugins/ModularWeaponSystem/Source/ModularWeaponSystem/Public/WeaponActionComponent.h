// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "WeaponActionComponent.generated.h"

class AWeapon;

UCLASS(Abstract)
class MODULARWEAPONSYSTEM_API UWeaponActionComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	virtual bool OnActionPressed(AWeapon* OwningWeapon) PURE_VIRTUAL(URangedActionComponent::TryUse, return false;);
	virtual bool OnActionHeld(float deltaTime, AWeapon* OwningWeapon) PURE_VIRTUAL(URangedActionComponent::TryUse, return false;);
	virtual void OnActionReleased() PURE_VIRTUAL(URangedActionComponent::TryUse, return;);
};

UCLASS(Abstract)
class MODULARWEAPONSYSTEM_API URangedActionComponent : public UWeaponActionComponent
{
	GENERATED_BODY()
public:
	virtual bool OnActionPressed(AWeapon* OwningWeapon) override { return false; }
	virtual bool OnActionHeld(float deltaTime, AWeapon* OwningWeapon) override { return false; }
	virtual void OnActionReleased() override { }
protected:
	bool Reload(AWeapon* OwningWeapon);
};

UCLASS()
class MODULARWEAPONSYSTEM_API USingleShotAction : public URangedActionComponent
{
	GENERATED_BODY()
public:
	virtual bool OnActionPressed(AWeapon* OwningWeapon) override;
	virtual void OnActionReleased() override;
private:
	bool bReleased = true;
};

UCLASS()
class MODULARWEAPONSYSTEM_API UAutomaticShotAction : public URangedActionComponent
{
	GENERATED_BODY()
public:
	virtual bool OnActionHeld(float deltaTime, AWeapon* OwningWeapon) override;
private:
	float LastFire = 0.f;
};

UCLASS(Abstract)
class MODULARWEAPONSYSTEM_API UMeleeActionComponent : public UWeaponActionComponent
{
	GENERATED_BODY()	
public:
	virtual bool OnActionPressed(AWeapon* OwningWeapon) override { return false; }
	virtual bool OnActionHeld(float deltaTime, AWeapon* OwningWeapon) override { return false; }
	virtual void OnActionReleased() override { }
};
