// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "WeaponActionComponent.generated.h"

class AWeapon;

UCLASS()
class MODULARWEAPONSYSTEM_API UWeaponActionComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	virtual bool TryUse(AWeapon* OwningWeapon) { return false; }
};

UCLASS()
class MODULARWEAPONSYSTEM_API URangedActionComponent : public UWeaponActionComponent
{
	GENERATED_BODY()
public:
	virtual bool TryUse(AWeapon* OwningWeapon) override PURE_VIRTUAL(URangedActionComponent::TryUse, return false;);
};

UCLASS()
class MODULARWEAPONSYSTEM_API UMeleeActionComponent : public UWeaponActionComponent
{
	GENERATED_BODY()	
public:
	virtual bool TryUse(AWeapon* OwningWeapon) override PURE_VIRTUAL(URangedActionComponent::TryUse, return false;);
};
