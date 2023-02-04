#pragma once

#include "VRConstants.h"
#include "GameFramework/GameUserSettings.h"
#include "VRGameUserSettings.generated.h"

UCLASS(BlueprintType, Config = Game)
class UVRGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetSnapTurnAngle(float AngleInDegrees);
	
	UFUNCTION(BlueprintPure, Category = Settings)
	float GetSnapTurnAngle();

	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetVRMovementMode(EVRMovementMode NewMovementMode);
	
	UFUNCTION(BlueprintPure, Category = Settings)
	EVRMovementMode GetVRMovementMode();
	
protected:
	
	UPROPERTY(Config, EditAnywhere, Category = "Turn")
	float SnapTurnAngle = 45.f;

	UPROPERTY(Config, EditAnywhere, Category = "Movement")
	EVRMovementMode MovementMode = EVRMovementMode::Blink;
	
};