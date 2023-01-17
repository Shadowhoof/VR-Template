#pragma once

#include "CoreMinimal.h"
#include "InputConfig.generated.h"

class UInputAction;

UCLASS()
class UInputConfig : public UDataAsset
{
    GENERATED_BODY()

public:

    // movement and looking around
    
    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    TObjectPtr<UInputAction> Move;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    TObjectPtr<UInputAction> Look;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    TObjectPtr<UInputAction> SnapTurn;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    TObjectPtr<UInputAction> Teleport;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    TObjectPtr<UInputAction> CancelTeleport;

    // hands

    UPROPERTY(EditDefaultsOnly, Category = "Hands")
    TObjectPtr<UInputAction> HandGraspLeft;

    UPROPERTY(EditDefaultsOnly, Category = "Hands")
    TObjectPtr<UInputAction> IndexFingerCurlLeft;

    UPROPERTY(EditDefaultsOnly, Category = "Hands")
    TObjectPtr<UInputAction> IndexFingerPointLeft;

    UPROPERTY(EditDefaultsOnly, Category = "Hands")
    TObjectPtr<UInputAction> ThumbUpLeft;

    UPROPERTY(EditDefaultsOnly, Category = "Hands")
    TObjectPtr<UInputAction> HandGraspRight;

    UPROPERTY(EditDefaultsOnly, Category = "Hands")
    TObjectPtr<UInputAction> IndexFingerCurlRight;

    UPROPERTY(EditDefaultsOnly, Category = "Hands")
    TObjectPtr<UInputAction> IndexFingerPointRight;

    UPROPERTY(EditDefaultsOnly, Category = "Hands")
    TObjectPtr<UInputAction> ThumbUpRight;
};