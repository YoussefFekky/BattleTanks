// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	class UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.f;

	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	virtual void SetPawn(APawn* InPawn) override;

	void AimAtCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	FVector2D GetCrosshairScreenLocation() const;

	UFUNCTION()
	void OnTankDeath();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void AimingComponentFound(class UTankAimingComponent* AimingComponent);

};
