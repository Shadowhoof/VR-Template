// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "VR/VRConstants.h"
#include "VRCharacter.generated.h"

class UMotionControllerComponent;
class UCameraComponent;
class UTeleportComponent;
class UNiagaraSystem;
class UInputConfig;
struct FInputActionInstance;

UCLASS()
class VRTEMPLATE_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVRCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VR")
	TObjectPtr<UMotionControllerComponent> LeftController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VR")
	TObjectPtr<UMotionControllerComponent> RightController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Teleport")
	TObjectPtr<UTeleportComponent> TeleportComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Teleport")
	TObjectPtr<UNiagaraSystem> TeleportFX;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	EVRMovementMode MovementMode = EVRMovementMode::Blink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputConfig> InputConfig;
	
protected:

	virtual void BeginPlay() override;

	void Move(const FInputActionInstance& Instance);
	void Look(const FInputActionInstance& Instance);
	void SnapTurn(const FInputActionInstance& Instance);
	
	void StartTeleport();
	void FinishTeleport();
	void CancelTeleport();

	FVector GetMovementForwardVector() const;
	FVector GetMovementRightVector() const;
	
};
