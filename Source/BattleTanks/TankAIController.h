// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
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
	
	ATank* ControlledTank = nullptr;
	ATank* PlayerTank = nullptr;
	float AcceptanceRadius = 0.f;
};
