// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	float NewRelativeRotation = FMath::Clamp<float>(RelativeRotation.Pitch + ElevationChange, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(NewRelativeRotation, 0, 0));
}
