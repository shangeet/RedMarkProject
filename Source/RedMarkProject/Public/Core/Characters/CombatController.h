// Project Red Mark

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class REDMARKPROJECT_API CombatController
{
public:
	CombatController(class USkeletalMeshComponent* playerMeshComponent, class UAnimMontage* combatMontage);

	void Attack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anims")
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
	class USkeletalMeshComponent* PlayerMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	class UAnimMontage* CombatMontage;
};
