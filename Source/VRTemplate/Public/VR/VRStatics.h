#pragma once

#include "VRStatics.generated.h"

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
};
