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

	virtual void BeginPlay() override;

	virtual void Tick(float) override;

private:
	class UTankAimingComponent* AimingComponent = nullptr;
	APawn* PlayerTank = nullptr;
	float AcceptanceRadius = 300.f;
};
