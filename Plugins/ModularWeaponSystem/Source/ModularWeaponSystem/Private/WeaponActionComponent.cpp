// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/WeaponActionComponent.h"

#include "Weapon.h"
#include "WeaponDataAsset.h"

bool USingleShotAction::OnActionPressed(AWeapon* OwningWeapon)
{
	if (!OwningWeapon || !OwningWeapon->WeaponData || !bReleased)
	{
		return false;
	}
	
	bReleased = false;
	
	URangedWeaponDataAsset* WeaponData = Cast<URangedWeaponDataAsset>(OwningWeapon->WeaponData);
	if(!WeaponData)
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
	
	// Maybe moved more general
	FVector StartPoint = FVector(0,0,5); // replace by socket
	FVector EndPoint = StartPoint + OwningWeapon->GetActorForwardVector() * WeaponData->Range;
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility);
	
	return true;
}

void USingleShotAction::OnActionReleased()
{
	bReleased = true;
}
