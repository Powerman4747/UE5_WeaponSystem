// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ReloadComponent.h"

#include "../Public/Weapon.h"
#include "../Public/WeaponDataAsset.h"
#include "Runtime/Engine/Classes/Engine/TimerHandle.h"
#include "Runtime/Engine/Public/TimerManager.h"

void UMagazineComponent::ConsumeAmmo(int Amount)
{
	CurrentAmmo = FMath::Max(0, CurrentAmmo - Amount);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::FromInt(CurrentAmmo));
}

bool UMagazineComponent::CanReload(AWeapon* OwningWeapon)
{
	if (!OwningWeapon || !OwningWeapon->WeaponData)
	{
		return false;
	}
	
	URangedWeaponDataAsset* WeaponData = Cast<URangedWeaponDataAsset>(OwningWeapon->WeaponData);
	return WeaponData && !IsReloading && CurrentAmmo < WeaponData->MagazineSize && CurrentMagazine > 0;
}

bool UMagazineComponent::TryReload(AWeapon* OwningWeapon)
{
	if (!CanReload(OwningWeapon))
	{
		return false;
	}
	
	IsReloading = true;
	
	URangedWeaponDataAsset* WeaponData = Cast<URangedWeaponDataAsset>(OwningWeapon->WeaponData);
	
	FTimerHandle ReloadTimerHandle;
	TFunction<void()>&& Callback = [this, WeaponData]()
	{
		CurrentAmmo = WeaponData->MagazineSize;
		IsReloading = false;
		CurrentMagazine--;
	};
	
	OwningWeapon->GetWorldTimerManager().SetTimer(ReloadTimerHandle, MoveTemp(Callback), WeaponData->ReloadTime, false);
	
	return  true;
}
