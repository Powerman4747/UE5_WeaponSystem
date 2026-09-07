// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Weapon.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "../Public/WeaponDataAsset.h"
#include "../Public/WeaponActionComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	auto MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
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
	
	const auto WeaponActionComponent = WeaponData->GetActionComponent();	
	if (WeaponActionComponent)
	{
		ActionComponent = NewObject<UWeaponActionComponent>(this, WeaponActionComponent);
		ActionComponent->RegisterComponent();
	}
	
	const auto WeaponCollisionComponent = WeaponData->GetCollisionComponent();	
	if (WeaponCollisionComponent)
	{
		CollisionComponent = NewObject<UWeaponCollisionComponent>(this, WeaponCollisionComponent);
		CollisionComponent->RegisterComponent();
	}
	else
	{
		TSubclassOf<UWeaponCollisionComponent> CollisionComp;

		if (WeaponData->IsA<URangedWeaponDataAsset>())      CollisionComp = URangedCollisionComponent::StaticClass();
		else if (WeaponData->IsA<UMeleeWeaponDataAsset>())  CollisionComp = nullptr; // UMeleeCollisionComponent::StaticClass(); not implemented yet

		if (!CollisionComp) return;

		CollisionComponent = NewObject<UWeaponCollisionComponent>(this, CollisionComp);
		CollisionComponent->RegisterComponent();
	}
	
	// Weapon type specific
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

void AWeapon::OnActionPressed()
{
	ActionComponent->OnActionPressed(this);
}

void AWeapon::OnActionReleased()
{
	ActionComponent->OnActionReleased();
}

void AWeapon::OnActionHeld(float dt)
{
	ActionComponent->OnActionHeld(dt, this);
}
