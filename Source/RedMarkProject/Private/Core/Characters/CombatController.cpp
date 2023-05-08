// Project Red Mark


#include "Core/Characters/CombatController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

/// <summary>
/// Ctor
/// </summary>
/// <param name="playerMeshComponent">Mesh component of the player or entity using the combat controller</param>
CombatController::CombatController(USkeletalMeshComponent* playerMeshComponent, UAnimMontage* combatMontage)
{
	PlayerMeshComponent = playerMeshComponent;
	CombatMontage = combatMontage;
}

/// <summary>
/// Plays the attack animation from the Combat montage
/// </summary>
void CombatController::Attack()
{
	bIsAttacking = true;
	UAnimInstance* animInstance = PlayerMeshComponent->GetAnimInstance();

	if (animInstance && CombatMontage)
	{
		animInstance->Montage_Play(CombatMontage, 1.0f);
		animInstance->Montage_JumpToSection(FName("Attack_1"), CombatMontage);
	}
}
