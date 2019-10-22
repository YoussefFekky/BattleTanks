// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	TArray<ASprungWheel*> SprungWheels;
	for (USceneComponent* Child : Children) {
		USpawnPoint* SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;
		AActor* SpawnedActor = SpawnPointChild->GetSpawnedActor();
		ASprungWheel* SprungWheel = Cast<ASprungWheel>(SpawnedActor);
		if (!ensure(SprungWheel)) continue;
		SprungWheels.Add(SprungWheel);
	}
	return SprungWheels;
}

void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp<float>(Throttle, -1.f, 1.f);
	DriveTrack(Throttle);
}

void UTankTrack::DriveTrack(float Throttle)
{
	TArray<ASprungWheel*> Wheels = GetWheels();
	float AppliedForcePerWheel = Throttle * MaxDrivingForce / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels) {
		Wheel->AddDrivingForce(AppliedForcePerWheel);
	}
}
