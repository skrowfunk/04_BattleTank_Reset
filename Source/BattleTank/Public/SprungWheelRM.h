// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheelRM.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheelRM : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheelRM();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetupConstraint();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
	
};
