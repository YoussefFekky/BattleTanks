// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 80000.f;

private:
	class UTankAimingComponent* AimingComponent = nullptr;
	class ATank* PossessedTank = nullptr;
	APawn* PlayerTank = nullptr;

	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();
};
