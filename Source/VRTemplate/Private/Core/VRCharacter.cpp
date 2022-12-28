// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VRCharacter.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "VR/VRSettings.h"
#include "VR/VRStatics.h"

AVRCharacter::AVRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->bLockToHmd = true;
	CameraComponent->SetupAttachment(RootComponent);
	
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftController->SetTrackingSource(EControllerHand::Left);
	LeftController->SetupAttachment(RootComponent);
	
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetTrackingSource(EControllerHand::Right);
	RightController->SetupAttachment(RootComponent);
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

void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UVRStatics::IsHMDActive())
	{
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
	}
}

void AVRCharacter::MoveForward(const float Value)
{
	AddMovementInput(GetMovementForwardVector(), Value);
}

void AVRCharacter::MoveRight(const float Value)
{
	AddMovementInput(GetMovementRightVector(), Value);
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

FVector AVRCharacter::GetMovementForwardVector() const
{
	if (!UVRStatics::IsHMDActive())
	{
		return GetActorForwardVector();
	}

	FVector ForwardVector = GetActorForwardVector();
	switch(MovementMode)
	{
	case EVRMovementMode::ContinuousHead:
		ForwardVector = CameraComponent->GetForwardVector();
		break;
	case EVRMovementMode::ContinuousControllers:
		ForwardVector = (LeftController->GetForwardVector() + RightController->GetForwardVector()) / 2;
		break;
	default:
		break;
	}

	return ForwardVector.GetSafeNormal2D();
}

FVector AVRCharacter::GetMovementRightVector() const
{
	if (!UVRStatics::IsHMDActive())
	{
		return GetActorRightVector();
	}

	FVector RightVector = GetActorRightVector();
	switch(MovementMode)
	{
	case EVRMovementMode::ContinuousHead:
		RightVector = CameraComponent->GetRightVector();
		break;
	case EVRMovementMode::ContinuousControllers:
		RightVector = (LeftController->GetRightVector() + RightController->GetRightVector()) / 2;
		break;
	default:
		break;
	}

	return RightVector.GetSafeNormal2D();
}

