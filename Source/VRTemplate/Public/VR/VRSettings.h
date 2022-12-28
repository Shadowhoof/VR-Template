#pragma once

#include "VRConstants.h"
#include "VRSettings.generated.h"

UCLASS(Config = VR)
class UVRSettings : public UObject
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, Category = "Turn")
	float SnapTurnAngle = 45.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	EVRMovementMode MovementMode = EVRMovementMode::Blink;
};