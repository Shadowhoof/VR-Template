#pragma once

#include "CoreMinimal.h"
#include "InputConfig.generated.h"

class UInputAction;

UCLASS()
class UInputConfig : public UDataAsset
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> Move;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> Look;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> SnapTurn;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> Teleport;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> CancelTeleport;
    
};