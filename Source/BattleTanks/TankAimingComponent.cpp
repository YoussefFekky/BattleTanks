// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float LaunchSpeed)
{
	FVector LaunchVelocity;
	if ( UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, Barrel->GetSocketLocation(FName("Projectile")), 
		TargetLocation, LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace) ) {
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s."), *GetOwner()->GetName(), *LaunchVelocity.GetSafeNormal().ToString());
		MoveBarrel(LaunchVelocity.GetSafeNormal());
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelReference)
{
	Barrel = BarrelReference;
}

void UTankAimingComponent::MoveBarrel(const FVector& AimDirection)
{
	if (!Barrel) return;
	FRotator RotationDifference = AimDirection.Rotation() - Barrel->GetComponentRotation();
	Barrel->Elevate(5.f);
	//UE_LOG(LogTemp, Warning, TEXT("Barrel rotation: %s"), *RotationDifference.ToString());
}
