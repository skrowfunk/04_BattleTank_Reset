// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "SprungWheel.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(MassWheelConstraint);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if (GetRootComponent())
	{
		UE_LOG(LogTemp, Warning, TEXT("GetRootComponent: %s"), *GetRootComponent()->GetName());

		if (GetRootComponent()->GetAttachParent())
		{
			UE_LOG(LogTemp, Warning, TEXT("GetAttachParent: %s"), *GetRootComponent()->GetAttachParent()->GetName());

			if (GetRootComponent()->GetAttachParent()->GetOwner())
			{
				UE_LOG(LogTemp, Warning, TEXT("GetOwner: %s"), *GetRootComponent()->GetAttachParent()->GetOwner()->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("GetOwner is Null"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GetAttachParent is Null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GetRootComponent is Null"));
	}

	SetupConstraint();

	if (GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("(3) Not Null: %s"), *GetAttachParentActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("(3) Null"));
	}
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



