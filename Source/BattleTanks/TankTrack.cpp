// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::DriveTrack()
{
	FVector AppliedForce = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(AppliedForce, GetComponentLocation());
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.f, 1.f);
	DriveTrack();
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.f;
}

void UTankTrack::ApplySidewaysForce()
{
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	FVector CorrectionAcceleration = -SlippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;

	TankRoot->AddForce(CorrectionForce);
}