// Project Red Mark

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSwitch.generated.h"

UCLASS()
class REDMARKPROJECT_API ABaseSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	// Dimensions for trigger needed to activate the switch (changes the height/length/width of the collider)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Triggers)
	FVector BoxSizeExtent = FVector(62.f, 62.f, 62.f);

	// Reference to the trigger
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Triggers)
	class UBoxComponent* TriggerBoxComponent;
	

};
