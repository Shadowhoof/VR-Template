#pragma once

#include "VRStatics.generated.h"

class UVRGameUserSettings;


UCLASS()
class UVRStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * @brief Checks whether a head-mounted display is currently active
	 * @return is there an active HMD
	 */
	UFUNCTION(BlueprintCallable)
	static bool IsHMDActive();

	UFUNCTION(BlueprintCallable, BlueprintPure, DisplayName = "Get VR User Settings")
	static UVRGameUserSettings* GetVRUserSettings();
};
