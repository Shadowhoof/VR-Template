// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VRCharacter.h"
#include "VR/VRSettings.h"

AVRCharacter::AVRCharacter()
{
}

void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	DECLARE_DELEGATE_OneParam(FSnapTurnDelegate, float)
	PlayerInputComponent->BindAction<FSnapTurnDelegate>("SnapTurnLeft", IE_Pressed, this, &AVRCharacter::SnapTurn, -1.f);
	PlayerInputComponent->BindAction<FSnapTurnDelegate>("SnapTurnRight", IE_Pressed, this, &AVRCharacter::SnapTurn, 1.f);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AVRCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVRCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AVRCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AVRCharacter::LookRight);
}

void AVRCharacter::MoveForward(const float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AVRCharacter::MoveRight(const float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AVRCharacter::LookUp(const float Value)
{
	AddControllerPitchInput(Value);
}

void AVRCharacter::LookRight(const float Value)
{
	AddControllerYawInput(Value);
}

void AVRCharacter::SnapTurn(const float Side)
{
	AddControllerYawInput(Side * GetDefault<UVRSettings>()->SnapTurnAngle);
}

