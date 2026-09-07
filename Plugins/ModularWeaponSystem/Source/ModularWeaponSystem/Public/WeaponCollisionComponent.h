// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "WeaponCollisionComponent.generated.h"

class AWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorHit, const FHitResult&, HitResult);

UCLASS(Abstract)
class MODULARWEAPONSYSTEM_API UWeaponCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Weapon")
	FOnActorHit OnActorHit;
	
	virtual bool DetectHit(AWeapon* OwningWeapon, TArray<FHitResult>& OutHits) PURE_VIRTUAL(UWeaponCollisionComponent::DetectHit, return false;);
	virtual void ResetDetection() {} // meant for melee weapons
};

UCLASS()
class MODULARWEAPONSYSTEM_API URangedCollisionComponent : public UWeaponCollisionComponent
{
	GENERATED_BODY()

public:	
	virtual bool DetectHit(AWeapon* OwningWeapon, TArray<FHitResult>& OutHits) override;
};