// Project Red Mark


#include "Core/Characters/MainCharacterAnimInstance.h"
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

	if (MainCharacter == nullptr)
	{
		MainCharacter = TryGetPawnOwner();
	}

	if (MainCharacter)
	{
		FVector Speed = MainCharacter->GetVelocity();
		FVector XSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = XSpeed.Size();

		bIsJumping = MainCharacter->GetMovementComponent()->IsFalling();
	}
}