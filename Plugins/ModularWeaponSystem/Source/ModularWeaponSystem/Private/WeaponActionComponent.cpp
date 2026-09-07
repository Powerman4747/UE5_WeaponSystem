// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/WeaponActionComponent.h"

#include "Weapon.h"
#include "WeaponDataAsset.h"

bool USingleShotAction::OnActionPressed(AWeapon* OwningWeapon)
{
	// validate data
	if (!OwningWeapon || !OwningWeapon->WeaponData || !bReleased)
	{
		return false;
	}
	
	bReleased = false;
	
	// validate asset
	URangedWeaponDataAsset* WeaponData = Cast<URangedWeaponDataAsset>(OwningWeapon->WeaponData);
	if(!WeaponData)
	{
		return false;
	}
	
	// validate ammo
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
	
	TArray<FHitResult> OutHits = TArray<FHitResult>();
	OwningWeapon->GetCollisionComponent()->DetectHit(OwningWeapon, OutHits);
	return true;
}

void USingleShotAction::OnActionReleased()
{
	bReleased = true;
}

bool UAutomaticShotAction::OnActionHeld(float deltaTime, AWeapon* OwningWeapon)
{
	// validate data
	if (!OwningWeapon || !OwningWeapon->WeaponData)
	{
		return false;
	}
	
	// validate data asset
	URangedWeaponDataAsset* WeaponData = Cast<URangedWeaponDataAsset>(OwningWeapon->WeaponData);
	if(!WeaponData)
	{
		return false;
	}

	// validate ammo
	if (OwningWeapon->GetReloadComponent() && !OwningWeapon->GetReloadComponent()->HasAmmo())
	{	
		return false;
	}
	
	// validate fire rate cooldown
	const float CurrentTime = OwningWeapon->GetWorld()->GetTimeSeconds();
	const float FireInterval = FMath::Max(WeaponData->FireRate, 0.0001f);
	if (CurrentTime - LastFire < FireInterval)
	{
		return false;
	}
	LastFire = CurrentTime;
	
	// without reload component infinite ammo
	if (OwningWeapon->GetReloadComponent())
	{
		OwningWeapon->GetReloadComponent()->ConsumeAmmo(1);
	}
	
	// Maybe moved more general
	FVector StartPoint = FVector(0,0,5); // replace by socket
	FVector EndPoint = StartPoint + OwningWeapon->GetActorForwardVector() * WeaponData->Range;
	FHitResult Hit;
	OwningWeapon->GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility);
	
	return true;
}
