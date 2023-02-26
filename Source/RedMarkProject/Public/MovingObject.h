// Project Red Mark

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObject.generated.h"

UCLASS(ABSTRACT)
class REDMARKPROJECT_API AMovingObject : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AMovingObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ActorMeshComponents")
	UStaticMeshComponent* BaseStaticMesh;

	// The starting location of the actor
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Customization Variables")
	FVector InitialLocation;

	// The current location of the actor
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Customization Variables")
	FVector CurrentLocation; 

	// The velocity of the moving actor
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Customization Variables")
	FVector DeltaVelocity;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
