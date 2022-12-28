#include "VR/VRStatics.h"

#include "IXRTrackingSystem.h"

bool UVRStatics::IsHMDActive()
{
	return GEngine->XRSystem && GEngine->XRSystem->IsHeadTrackingAllowed();
}
