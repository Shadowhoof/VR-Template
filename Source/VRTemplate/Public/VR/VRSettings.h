#pragma once

#include "VRConstants.h"

UCLASS(Config = VR)
class UVRSettings : public UObject
{
public:
	
	UPROPERTY(EditAnywhere, Category = "Turn")
	float SnapTurnAngle = 45.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	EVRMovementMode MovementMode = EVRMovementMode::Blink;
};