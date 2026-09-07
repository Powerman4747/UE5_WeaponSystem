// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReloadComponent.h"
#include "WeaponActionComponent.h"
#include "WeaponCollisionComponent.h"
#include "Runtime/Engine/Classes/Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */

static const FPrimaryAssetType WeaponAssetType = TEXT("Weapon");


UCLASS(Abstract)
class MODULARWEAPONSYSTEM_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info, meta = (DisplayPriority = -1))
	FText DisplayName = FText::FromString("");
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info, meta = (DisplayPriority = 0))
	float Damage = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Assets, meta = (AssetBundles = "WeaponAssets"))
	TSoftObjectPtr<UStaticMesh> WeaponMesh;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(WeaponAssetType, GetFName());
	}
	
	virtual TSubclassOf<UWeaponActionComponent> GetActionComponent() const PURE_VIRTUAL(UWeaponDataAsset::GetActionComponent, return nullptr;);
	virtual TSubclassOf<UWeaponCollisionComponent> GetCollisionComponent() const PURE_VIRTUAL(UWeaponDataAsset::GetCollisionComponent, return nullptr;);
};

UCLASS()
class MODULARWEAPONSYSTEM_API URangedWeaponDataAsset : public UWeaponDataAsset
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info)
	float FireRate = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info)
	int MaxMagazines = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info)
	int MagazineSize = 30;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info)
	float ReloadTime = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info)
	float Range = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (DisallowAbstractClasses))
	TSubclassOf<URangedActionComponent> ActionComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (DisallowAbstractClasses))
	TSubclassOf<UReloadComponent> ReloadComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	TSubclassOf<URangedCollisionComponent> CollisionComponent = URangedCollisionComponent::StaticClass();
	
	virtual TSubclassOf<UWeaponActionComponent> GetActionComponent() const override
	{
		return ActionComponent;
	}
	
	virtual TSubclassOf<UWeaponCollisionComponent> GetCollisionComponent() const override
	{
		return CollisionComponent;
	}

};

UCLASS()
class MODULARWEAPONSYSTEM_API UMeleeWeaponDataAsset : public UWeaponDataAsset
{
	GENERATED_BODY()
	
public:		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	TSubclassOf<UMeleeActionComponent> ActionComponent;
	
	// CollisionComponent
	
	virtual TSubclassOf<UWeaponActionComponent> GetActionComponent() const override
	{
		return ActionComponent;
	}
	
	virtual TSubclassOf<UWeaponCollisionComponent> GetCollisionComponent() const override
	{
		return nullptr;
	}
};
