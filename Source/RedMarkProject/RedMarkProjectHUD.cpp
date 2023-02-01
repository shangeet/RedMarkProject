
#include "RedMarkProjectHUD.h"
#include "Components/ProgressBar.h"

void URedMarkProjectHUD::SetHealth(float CurrentHealth, float MaxHealth)
{
	/** Set amount of health bar that will show as full **/
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}

}

void URedMarkProjectHUD::SetStamina(float CurrentStamina, float MaxStamina)
{
	/** Set amount of stamina bar that will show as full **/
	if (StaminaBar)
	{
		StaminaBar->SetPercent(CurrentStamina / MaxStamina);
	}
}