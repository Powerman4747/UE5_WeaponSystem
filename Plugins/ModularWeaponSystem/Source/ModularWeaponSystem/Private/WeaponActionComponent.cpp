// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/WeaponActionComponent.h"

#include "Weapon.h"
#include "WeaponDataAsset.h"

bool USingleShotAction::TryUse(struct FHitResult& Hit, AWeapon* OwningWeapon)
{
	if (!OwningWeapon || !OwningWeapon->WeaponData)
	{
		return false;
	}
	
	URangedWeaponDataAsset* WeaponData = Cast<URangedWeaponDataAsset>(OwningWeapon->WeaponData);
	
	if(!WeaponData)
	{
		return false;
	}
	
	const float CurrentTime = OwningWeapon->GetWorld()->GetTimeSeconds();
	const float FireInterval = FMath::Max(WeaponData->FireRate, 0.0001f);
	if (CurrentTime - LastFireTime < FireInterval)
	{
		return false;
	}
	
	if (OwningWeapon->GetReloadComponent() && !OwningWeapon->GetReloadComponent()->HasAmmo())
	{	
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Out of Ammo"));
		return false;
	}
	
	// without reload component infinite ammo
	if (OwningWeapon->GetReloadComponent())
	{
		OwningWeapon->GetReloadComponent()->ConsumeAmmo(1);
	}
	
	LastFireTime = CurrentTime;
	
	// Maybe moved more general
	FVector StartPoint = FVector(0,0,5); // replace by socket
	FVector EndPoint = StartPoint + OwningWeapon->GetActorForwardVector() * WeaponData->Range;
	GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility);
	
	return true;
}
