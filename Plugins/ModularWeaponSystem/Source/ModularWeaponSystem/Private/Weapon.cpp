// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Weapon.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "../Public/WeaponDataAsset.h"
#include "../Public/WeaponActionComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Initialize(UWeaponDataAsset* InWeaponData)
{
	if (!InWeaponData) return;
	
	WeaponData = InWeaponData;
	
	const auto ActionComponent = WeaponData->GetActionComponent();	
	if (ActionComponent)
	{
		WeaponActionComponent = NewObject<UWeaponActionComponent>(this, ActionComponent);
		WeaponActionComponent->RegisterComponent();
	}
	
	const auto* RangedData = Cast<URangedWeaponDataAsset>(WeaponData);	
	if (RangedData)
	{
		if (RangedData->ReloadComponent)
		{
			ReloadComponent = NewObject<UReloadComponent>(this, RangedData->ReloadComponent);
			ReloadComponent->RegisterComponent();
			ReloadComponent->TryReload(this); // maybe move to init function for mag initialization
		}
	}
}

void AWeapon::TryUse(FHitResult& Hit)
{
	WeaponActionComponent->TryUse(Hit, this);
}
