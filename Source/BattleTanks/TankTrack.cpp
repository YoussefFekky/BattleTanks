// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1.f, 1.f);
	FVector AppliedForce = GetForwardVector() * Throttle * MaxDrivingForce;
	UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(AppliedForce, GetComponentLocation());
}