// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */

static const FPrimaryAssetType WeaponAssetType = TEXT("Weapon");


UCLASS()
class MODULARWEAPONSYSTEM_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info)
	FText DisplayName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Info)
	float Damage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Assets, meta = (AssetBundles = "WeaponAssets"))
	TSoftObjectPtr<UStaticMesh> WeaponMesh;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(WeaponAssetType, GetFName());
	}
};

UCLASS()
class MODULARWEAPONSYSTEM_API URangedWeaponDataAsset : public UWeaponDataAsset
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Assets, meta = (AssetBundles = "WeaponAssets"))
	TSoftObjectPtr<UStaticMesh> BulletMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	TSubclassOf<URangedActionComponent> ActionComponent;
};

UCLASS()
class MODULARWEAPONSYSTEM_API UMeleeWeaponDataAsset : public UWeaponDataAsset
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Assets, meta = (AssetBundles = "WeaponAssets"))
	TSoftObjectPtr<UStaticMesh> BulletMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	TSubclassOf<UMeleeActionComponent> ActionComponent;
	
};
