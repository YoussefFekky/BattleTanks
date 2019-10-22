// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

protected:
	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;

	virtual float TakeDamage
	(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	FTankDelegate OnDeath;

};
