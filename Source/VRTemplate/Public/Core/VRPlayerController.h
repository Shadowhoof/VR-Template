// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VRPlayerController.generated.h"

class AVRCharacter;
class UVRGameUserSettings;
UCLASS(DisplayName="VR Player Controller")
class VRTEMPLATE_API AVRPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SaveUserSettings();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:

	UPROPERTY()
	TObjectPtr<AVRCharacter> VRCharacter;
	
};
