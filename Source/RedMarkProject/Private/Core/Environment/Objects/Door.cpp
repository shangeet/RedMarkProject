// Project Red Mark

#include "Core/Environment/Objects/Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Quat.h"

// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerBoxComponent->SetBoxExtent(BoxSizeExtent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(GetRootComponent());

	DoorMeshColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorMeshCollider"));
	DoorMeshColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DoorMeshColliderComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	DoorMeshColliderComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	DoorMeshColliderComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	DoorMeshColliderComponent->SetupAttachment(DoorMesh);

	// Don't set a rotate value initially
	GoalDoorRotator = FRotator(0.f, 0.f, 0.f);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
	TriggerBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentDoorRotator = DoorMesh->GetRelativeRotation();

	RotateDoor();

}

void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		FVector TriggerPawnLocation = OtherActor->GetActorLocation();
		FVector Direction = GetActorLocation() - TriggerPawnLocation;
		Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());

		if (Direction.X > 0.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("On overlap begin triggered: Open Positive Direction: %f"), Direction.X);
			GoalDoorRotator = FRotator(0.f, DoorOpenRotation, 0.f);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("On overlap begin triggered: Open Negative Direction %f"), Direction.X);
			GoalDoorRotator = FRotator(0.f, -1 * DoorOpenRotation, 0.f);
		}
	}
}

void ADoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("On overlap end triggered"));
		GoalDoorRotator = FRotator(0.f, DoorCloseRotation, 0.f);
	}
}

void ADoor::RotateDoor()
{
	DoorMesh->SetRelativeRotation(FMath::Lerp(FQuat(CurrentDoorRotator), FQuat(GoalDoorRotator), DoorLerpSpeed));
}
