// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Yaw(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float YawChange = RelativeSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	float NewRelativeYaw = RelativeRotation.Yaw + YawChange;

	SetRelativeRotation(FRotator(0.f, NewRelativeYaw, 0.f));
}