// Project Red Mark

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInput/Public/InputAction.h"
#include "InputConfigData.generated.h"

/**
 * 
 */
UCLASS()
class REDMARKPROJECT_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputActionMove;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputActionLook;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* InputActionJump;
};
