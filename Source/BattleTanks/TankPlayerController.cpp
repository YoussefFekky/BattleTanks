// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();
	
	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<class UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		AimingComponentFound(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!ensure(ControlledTank)) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		ControlledTank->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FVector2D CrosshairLocation = GetCrosshairScreenLocation();
	FVector WorldLocation, WorldDirection;
	if (DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, WorldLocation, WorldDirection)) {
		if (GetWorld()->LineTraceSingleByChannel(HitResult, PlayerCameraManager->GetCameraLocation(),
			ControlledTank->GetActorLocation() + LineTraceRange * WorldDirection,
			ECC_Visibility)) {
			OutHitLocation = HitResult.Location;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

FVector2D ATankPlayerController::GetCrosshairScreenLocation() const
{
	int32 ViewportXSize, ViewportYSize;
	GetViewportSize(ViewportXSize, ViewportYSize);
	FVector2D CrosshairLocation(ViewportXSize * CrosshairXLocation, ViewportYSize * CrosshairYLocation);
	return CrosshairLocation;
}

