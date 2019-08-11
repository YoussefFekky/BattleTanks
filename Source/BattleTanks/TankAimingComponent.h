// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	UTankBarrel* Barrel = nullptr;

	void MoveBarrel(const FVector&);

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector TargetLocation, float LaunchSpeed);

	void SetBarrelReference(UTankBarrel*);

};
