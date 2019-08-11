// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* ControlledTank = nullptr;
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f;

	ATank* GetControlledTank() const;
	void AimAtCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	FVector2D GetCrosshairScreenLocation() const;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float) override;

};
