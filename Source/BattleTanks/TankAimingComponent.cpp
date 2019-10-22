// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (Ammo < 1)
		FiringState = EFiringState::OutOfAmmo;
	else if (GetWorld()->GetTimeSeconds() < LastFireTime + ReloadTime)
		FiringState = EFiringState::Reloading;
	else if(IsBarrelMoving())
		FiringState = EFiringState::Aiming;
	else
		FiringState = EFiringState::Locked;
}

void UTankAimingComponent::Initialize(UTankTurret* TurretIn, UTankBarrel* BarrelIn, TSubclassOf<AProjectile> ProjectileIn)
{
	Turret = TurretIn;
	Barrel = BarrelIn;
	ProjectileBlueprint = ProjectileIn;
	CurrentAimDirection = Barrel->GetForwardVector();
}

int32 UTankAimingComponent::GetAmmo() const
{
	return Ammo;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::AimAt(FVector TargetLocation)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	FVector LaunchVelocity;
	if ( UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, Barrel->GetSocketLocation(FName("Projectile")), 
		TargetLocation, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace) ) {
		CurrentAimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(CurrentAimDirection);
		MoveTurret(CurrentAimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::Reloading || FiringState == EFiringState::OutOfAmmo) return;
	if (!ensure(Barrel) || !ensure(ProjectileBlueprint)) { return; }
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetComponentRotation())->LaunchProjectile(LaunchSpeed);
	Ammo--;
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::MoveBarrel(const FVector& AimDirection)
{
	if (ensure(Barrel)) {
		FRotator RotationDifference = AimDirection.Rotation() - Barrel->GetComponentRotation();
		Barrel->Elevate(RotationDifference.Pitch);
	}
}

void UTankAimingComponent::MoveTurret(const FVector& AimDirection)
{
	if (ensure(Turret)) {
		FRotator RotationDifference = AimDirection.Rotation() - Turret->GetComponentRotation();
		FMath::Abs(RotationDifference.Yaw) < 180? Turret->Yaw(RotationDifference.Yaw): Turret->Yaw(-RotationDifference.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	return !Barrel->GetForwardVector().Equals(CurrentAimDirection, 0.01);
}
