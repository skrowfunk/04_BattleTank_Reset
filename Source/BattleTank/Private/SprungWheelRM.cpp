// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "SprungWheelRM.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheelRM::ASprungWheelRM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheelRM::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetRootComponent())
	{
		UE_LOG(LogTemp, Warning, TEXT("(RM) GetRootComponent: %s"), *GetRootComponent()->GetName());

		if (GetRootComponent()->GetAttachParent())
		{
			UE_LOG(LogTemp, Warning, TEXT("(RM) GetAttachParent: %s"), *GetRootComponent()->GetAttachParent()->GetName());

			if (GetRootComponent()->GetAttachParent()->GetOwner())
			{
				UE_LOG(LogTemp, Warning, TEXT("(RM) GetOwner: %s"), *GetRootComponent()->GetAttachParent()->GetOwner()->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("(RM) GetOwner is Null"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("(RM) GetAttachParent is Null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("(RM) GetRootComponent is Null"));
	}

	SetupConstraint();

	if (GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("(RM) Not Null: %s"), *GetAttachParentActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("(RM) Null"));
	}
}

void ASprungWheelRM::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot)
	{
		UE_LOG(LogTemp, Warning, TEXT("(RM) No body root!"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("(RM) Body root found"));
	}
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheelRM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheelRM::AddDrivingForce(float ForceMagnitude)
{
	Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}

