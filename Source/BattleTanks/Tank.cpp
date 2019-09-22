// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankBarrel.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATank::AimAt(FVector TargetLocation)
{
	if(ensure(AimingComponent))
		AimingComponent->AimAt(TargetLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (GetWorld()->GetTimeSeconds() < LastFireTime + ReloadTime) return;
	if (!ensure(Barrel)) { return; }
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetComponentRotation())->LaunchProjectile(LaunchSpeed);
	LastFireTime = GetWorld()->GetTimeSeconds();
}