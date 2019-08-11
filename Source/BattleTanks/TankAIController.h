// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "Engine/World.h"
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
	
	ATank* GetControlledTank() const;

private:
	
	ATank* ControlledTank = nullptr;
	ATank* PlayerTank = nullptr;

	ATank* GetPlayerTank() const;

};
