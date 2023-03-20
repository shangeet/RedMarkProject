// Project Red Mark


#include "Core/Environment/Objects/MovingObject.h"

/*
This class is a base class for any non-living object (not character/AI) that can move. 
This is meant to be like an abstract class, and should not be implemented directly.
For example, a car object can be extended from this class. 
*/
AMovingObject::AMovingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("CustomStaticMesh");

	InitialLocation = FVector(0.0f, 0.0f, 0.0f);
	CurrentLocation = FVector(0.0f, 0.0f, 0.0f);
	DeltaVelocity = FVector(0.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void AMovingObject::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(InitialLocation);

	CurrentLocation = GetActorLocation();
}

// Called every frame
void AMovingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update location with velocity
	FHitResult hitResult;
	AddActorLocalOffset(DeltaVelocity, false, &hitResult);
	CurrentLocation = GetActorLocation();

}
