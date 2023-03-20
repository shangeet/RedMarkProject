// Project Red Mark

#pragma once

#include "CoreMinimal.h"
#include "Core/Environment/Objects/BaseSwitch.h"
#include "Door.generated.h"

/**
 * A switch that gets triggered
 */
UCLASS()
class REDMARKPROJECT_API ADoor : public ABaseSwitch
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void RotateDoor();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Colliders)
	class UBoxComponent* DoorMeshColliderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Customization)
	float DoorOpenRotation = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Customization)
	float DoorCloseRotation = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Customization)
	float DoorLerpSpeed = 0.01f;

	FRotator CurrentDoorRotator;

	FRotator GoalDoorRotator;

};
