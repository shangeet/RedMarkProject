// Project Red Mark


#include "MainCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"


void UMainCharacterAnimInstance::NativeInitializeAnimation()
{

	if (MainCharacter == nullptr)
	{
		MainCharacter = TryGetPawnOwner();
	}


}

void UMainCharacterAnimInstance::UpdateAnimationProperties()
{
	UE_LOG(LogTemp, Warning, TEXT("Updating animation properties"));

	if (MainCharacter == nullptr)
	{
		MainCharacter = TryGetPawnOwner();
	}

	if (MainCharacter)
	{
		FVector Speed = MainCharacter->GetVelocity();
		UE_LOG(LogTemp, Warning, TEXT("Speed: (%f , %f)"), Speed.X, Speed.Y);
		FVector XSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = XSpeed.Size();

		UE_LOG(LogTemp, Warning, TEXT("Movement Speed: %f"), MovementSpeed);

		bIsJumping = MainCharacter->GetMovementComponent()->IsFalling();
	}
}