// Project Red Mark

#pragma once

#include "CoreMinimal.h"
#include "Core/Characters/InputConfigData.h"
#include "GameFramework/Character.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "BaseCharacter.generated.h"

UCLASS()
class REDMARKPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ABaseCharacter(); 

	/** Functions */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles moving forward/backward
	void HandleInputMove(const FInputActionValue& PlayerInputActionValue);

	// Handles mouse and stick look
	void HandleInputLook(const FInputActionValue& PlayerInputActionValue);

	// Handles jumping
	void HandleInputJump(const FInputActionValue& PlayerInputActionValue);

public:

	/** Variables */ 

	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	// Follow camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	// Scales turning functionality
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera)
	float BaseTurnRate = 65.f;

	// Scales look up functionality
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Camera)
	float BaseLookupRate = 65.f;

	// Speed at which the character jumps
	UPROPERTY(VisibleAnywhere, BlueprintReadwrite, Category = Customization)
	float CharacterJumpSpeed = 650.f;

	// Rate at which the character stays in the air
	UPROPERTY(VisibleAnywhere, BlueprintReadwrite, Category = Customization)
	float AirControlRate = 0.2f;

	// Getters
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	
	// Input actions and mapping vars

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputConfigData* InputActions;

};
