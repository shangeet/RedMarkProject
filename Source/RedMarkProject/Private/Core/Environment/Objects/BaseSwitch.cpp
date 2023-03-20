// Project Red Mark


#include "Core/Environment/Objects/BaseSwitch.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseSwitch::ABaseSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComponent"));
	RootComponent = TriggerBoxComponent;

}

// Called when the game starts or when spawned
void ABaseSwitch::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {}
void ABaseSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {}

