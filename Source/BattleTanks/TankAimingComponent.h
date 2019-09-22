// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	class UTankBarrel* Barrel = nullptr;
	class UTankTurret* Turret = nullptr;

	void MoveBarrel(const FVector&);
	void MoveTurret(const FVector&);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
		EFiringState FiringStatus = EFiringState::Locked;

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankTurret* TurretIn, UTankBarrel* BarrelIn);

	void AimAt(FVector TargetLocation, float LaunchSpeed);
};
