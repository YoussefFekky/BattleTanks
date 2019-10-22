// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	class UTankBarrel* Barrel = nullptr;
	class UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Ballistics")
		float LaunchSpeed = 8000.f;

	TSubclassOf<class AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Ballistics")
		float ReloadTime = 2.f;

	float LastFireTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Ballistics")
	int32 Ammo = 15;

	FVector CurrentAimDirection;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveBarrel(const FVector&);
	void MoveTurret(const FVector&);

	bool IsBarrelMoving();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Ballistics")
		EFiringState FiringState = EFiringState::Reloading;

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankTurret* TurretIn, UTankBarrel* BarrelIn, TSubclassOf<class AProjectile> ProjectileIn);

	UFUNCTION(BlueprintCallable, Category = "Ballistics")
	int32 GetAmmo() const;

	EFiringState GetFiringState() const;

	void AimAt(FVector TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Ballistics")
		void Fire();
};
