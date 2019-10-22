// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassAxleConstraint"));
	SetRootComponent(MassAxleConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassAxleConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	
	SetupConstraint();

}

void ASprungWheel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentDrivingForce = 0.f;

}

void ASprungWheel::SetupConstraint()
{
	AActor* ParentActor = GetAttachParentActor();
	if (ParentActor) {
		UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(ParentActor->GetRootComponent());
		if (RootComponent) {
			MassAxleConstraint->SetConstrainedComponents(RootComponent, NAME_None,
				Cast<UPrimitiveComponent>(Axle), NAME_None);
			AxleWheelConstraint->SetConstrainedComponents(Cast<UPrimitiveComponent>(Axle), NAME_None,
				Cast<UPrimitiveComponent>(Wheel), NAME_None);
		}
	}
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	CurrentDrivingForce += ForceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Wheel->AddForce(Axle->GetForwardVector() * CurrentDrivingForce);
}
