// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSec = 20.f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevation = 0.f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevation = 30.f;
public:
	void Elevate(float);
	
};
