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

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 5000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<class AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTime = 3.f;

	float LastFireTime = 0.f;

	FVector AimDirection;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveBarrel(const FVector&);
	void MoveTurret(const FVector&);

	bool IsBarrelMoving();
	bool IsTurretMoving();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Firing")
		EFiringState FiringState = EFiringState::Reloading;

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankTurret* TurretIn, UTankBarrel* BarrelIn, TSubclassOf<class AProjectile> ProjectileIn);

	void AimAt(FVector TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Action")
		void Fire();
};
