

#include "Core/VRPlayerController.h"

#include "Core/VRCharacter.h"
#include "VR/VRGameUserSettings.h"
#include "VR/VRStatics.h"

void AVRPlayerController::SaveUserSettings()
{
	UVRGameUserSettings* Settings = UVRStatics::GetVRUserSettings();
	Settings->SaveConfig();

	if (VRCharacter)
	{
		VRCharacter->OnUserSettingsChanged();
	}
}

void AVRPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	VRCharacter = Cast<AVRCharacter>(InPawn);
}
