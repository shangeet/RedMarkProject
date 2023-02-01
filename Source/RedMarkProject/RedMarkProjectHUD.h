
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RedMarkProjectHUD.generated.h"

UCLASS(Abstract)
class REDMARKPROJECT_API URedMarkProjectHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Update HUD with current health. **/
	void SetHealth(float CurrentHealth, float MaxHealth);

	/** Update HUD with current stamina. **/
	void SetStamina(float CurrentStamina, float MaxStamina);

	/** Widget to use to display current health. **/
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* HealthBar;

	/** Widget to use to display current stamina. **/
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* StaminaBar;

};