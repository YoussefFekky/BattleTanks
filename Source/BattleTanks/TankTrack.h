// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UTankTrack();

	TArray<class ASprungWheel*> GetWheels() const;

	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);

protected:
	UPROPERTY(EditDefaultsOnly)
		float MaxDrivingForce = 30000000.f;

private:
	void DriveTrack(float Throttle);

};
