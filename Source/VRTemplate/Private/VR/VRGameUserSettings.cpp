#include "VR/VRGameUserSettings.h"

void UVRGameUserSettings::SetSnapTurnAngle(float AngleInDegrees)
{
	SnapTurnAngle = AngleInDegrees;
}

float UVRGameUserSettings::GetSnapTurnAngle()
{
	return SnapTurnAngle;
}

void UVRGameUserSettings::SetVRMovementMode(EVRMovementMode NewMovementMode)
{
	MovementMode = NewMovementMode;
}

EVRMovementMode UVRGameUserSettings::GetVRMovementMode()
{
	return MovementMode;
}
