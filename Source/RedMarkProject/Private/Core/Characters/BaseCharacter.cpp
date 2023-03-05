// Project Red Mark

#include "Core/Characters/BaseCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputActionValue.h"

/*
This base character class implements core functions of any character in the game, including the NPCs and Player.
This should not be implmented directly and is meant to be an "abstract" class, 
though Unreal doesn't really support them in the same way as Unity. 
*/
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera boom
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 600.0f; // The camera follows at this distance behind the character    
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Rotation should affect the Camera only, not the Controller
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Character turns in the direction the controller is moving, but only on the Y axis
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f); 
	GetCharacterMovement()->JumpZVelocity = CharacterJumpSpeed;
	GetCharacterMovement()->AirControl = AirControlRate;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	if (!PlayerInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInputComponent was null. Please make sure it's set in the blueprint."));
		return;
	}

	if (!InputActions)
	{
		UE_LOG(LogTemp, Error, TEXT("InputActions were null. Please make sure it's set in the blueprint."));
	}

	// Get the player controller
	APlayerController* playerController = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	// Clear out existing mapping, and add our mapping
	subSystem->ClearAllMappings();
	subSystem->AddMappingContext(InputMapping, 0);

	// Get the player's enchanced input component
	UEnhancedInputComponent* playerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind actions
	playerInputComponent->BindAction(InputActions->InputActionMove, ETriggerEvent::Triggered, this, &ABaseCharacter::HandleInputMove);
	playerInputComponent->BindAction(InputActions->InputActionLook, ETriggerEvent::Triggered, this, &ABaseCharacter::HandleInputLook);
	playerInputComponent->BindAction(InputActions->InputActionJump, ETriggerEvent::Triggered, this, &ABaseCharacter::HandleInputJump);

}

/**
* Takes input from the controller to move the character
* @param PlayerInputActionValue: The value the engine receives from a keyboard press/gamepad for moving 
*/
void ABaseCharacter::HandleInputMove(const FInputActionValue& PlayerInputActionValue)
{
	if (Controller)
	{
		const FVector2D MoveValue = PlayerInputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

		// Forward/Backward direction
		if (MoveValue.Y != 0.f)
		{
			// Get forward vector
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(Direction, MoveValue.Y);
		}

		// Right/Left direction
		if (MoveValue.X != 0.f)
		{
			// Get right vector
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

/**
* Takes input from the controller to rotate the character's view
* @param PlayerInputActionValue: The value the engine recevies from the mouse/gamepad for looking
*/
void ABaseCharacter::HandleInputLook(const FInputActionValue& PlayerInputActionValue)
{
	if (Controller)
	{
		const FVector2D LookValue = PlayerInputActionValue.Get<FVector2D>();

		if (LookValue.X != 0.f)
		{
			AddControllerYawInput(LookValue.X * BaseTurnRate * GetWorld()->GetDeltaSeconds());
		}

		if (LookValue.Y != 0.f)
		{
			AddControllerPitchInput(LookValue.Y * BaseLookupRate * GetWorld()->GetDeltaSeconds());
		}
	}
}

/**
* Takes input from the controller to make the character jump
* @param PlayerInputActionValue: The value the engine receives from the keyboard/gamepad for jumping
*/
void ABaseCharacter::HandleInputJump(const FInputActionValue& PlayerInputActionValue)
{
	bool bJumpPressed = PlayerInputActionValue.Get<bool>();
	if (Controller && !bWasJumping && bJumpPressed)
	{
		Jump();
	}
	else if (Controller && bWasJumping)
	{
		StopJumping();
	}
}

