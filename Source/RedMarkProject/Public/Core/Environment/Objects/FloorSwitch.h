// Project Red Mark

#pragma once

#include "CoreMinimal.h"
#include "Core/Environment/Objects/BaseSwitch.h"
#include "FloorSwitch.generated.h"

/**
 * A switch that gets triggered 
 */
UCLASS()
class REDMARKPROJECT_API AFloorSwitch : public ABaseSwitch
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AFloorSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
