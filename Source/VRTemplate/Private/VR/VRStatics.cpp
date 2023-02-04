#include "VR/VRStatics.h"

#include "IXRTrackingSystem.h"
#include "VR/VRGameUserSettings.h"

bool UVRStatics::IsHMDActive()
{
	return GEngine->XRSystem && GEngine->XRSystem->IsHeadTrackingAllowed();
}

UVRGameUserSettings* UVRStatics::GetVRUserSettings()
{
	return Cast<UVRGameUserSettings>(GEngine->GetGameUserSettings());
}
