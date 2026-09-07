#include "../Public/WeaponCollisionComponent.h"

#include "WeaponDataAsset.h"
#include "../Public/Weapon.h"

bool URangedCollisionComponent::DetectHit(AWeapon* OwningWeapon, TArray<FHitResult>& OutHits)
{
	URangedWeaponDataAsset* WeaponData = Cast<URangedWeaponDataAsset>(OwningWeapon->WeaponData);
	if(!WeaponData)
	{
		return false;
	}
	
	// Maybe moved more general
	FVector StartPoint = OwningWeapon->GetActorTransform().GetTranslation(); // replace by socket
	FVector EndPoint = StartPoint + OwningWeapon->GetActorForwardVector() * WeaponData->Range;
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility);
	DrawDebugLine(
		GetWorld(),
		StartPoint,
		EndPoint,
		FColor::Red,
		false,      
		10.0f,      // duration in seconds
		0,   
		5.0f        // thickness
	);
	
	OnActorHit.Broadcast(Hit);
	
	return true;
}
