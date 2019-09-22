// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackIn, UTankTrack* RightTrackIn)
{
	LeftTrack = LeftTrackIn;
	RightTrack = RightTrackIn;
}

void UTankMovementComponent::MoveForward(float Throws)
{
	if (ensure(LeftTrack && RightTrack)) {
		LeftTrack->SetThrottle(Throws);
		RightTrack->SetThrottle(Throws);
	}
}

void UTankMovementComponent::MoveRight(float Throws)
{
	if (ensure(LeftTrack && RightTrack)) {
		LeftTrack->SetThrottle(Throws);
		RightTrack->SetThrottle(-Throws);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIIntention = MoveVelocity.GetSafeNormal();
	FVector TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	float ForwardThrow = FVector::DotProduct(TankForwardVector, AIIntention);
	MoveForward(ForwardThrow);

	float RightThrow = FVector::CrossProduct(TankForwardVector, AIIntention).Z;
	MoveRight(RightThrow);
}
