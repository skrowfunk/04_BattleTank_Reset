// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "SprungWheel2.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel2::ASprungWheel2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	SetRootComponent(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(MassWheelConstraint);
}

// Called when the game starts or when spawned
void ASprungWheel2::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("(2) Null"));

	if (GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("(2) Not Null: %s"), *GetAttachParentActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("(2) Null"));
	}

	SetupConstraint();

	
}

void ASprungWheel2::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

