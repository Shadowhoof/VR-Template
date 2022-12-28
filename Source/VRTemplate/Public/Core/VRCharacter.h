// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VR/VRConstants.h"
#include "VRCharacter.generated.h"

class UMotionControllerComponent;
class UCameraComponent;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	EVRMovementMode MovementMode = EVRMovementMode::Blink;
	
protected:

	virtual void BeginPlay() override;
	
	void MoveForward(const float Value);
	void MoveRight(const float Value);

	void LookUp(const float Value);
	void LookRight(const float Value);
	
	void SnapTurn(const float Side);

	FVector GetMovementForwardVector() const;
	FVector GetMovementRightVector() const;
	
};
