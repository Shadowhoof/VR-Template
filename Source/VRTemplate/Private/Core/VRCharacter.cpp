// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VRCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"
#include "VR/TeleportComponent.h"
#include "Input/InputConfig.h"
#include "VR/VRGameUserSettings.h"
#include "VR/VRStatics.h"
#include "VR/Hands/HandMeshComponent.h"

namespace MotionSourceName
{
	static const FName Left = "Left"; 
	static const FName Right = "Right"; 
	static const FName LeftAim = "LeftAim"; 
	static const FName RightAim = "RightAim"; 
}

AVRCharacter::AVRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->bLockToHmd = true;
	CameraComponent->SetupAttachment(RootComponent);
	
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftController->SetTrackingMotionSource(MotionSourceName::Left);
	LeftController->bDisplayDeviceModel = false;
	LeftController->SetupAttachment(RootComponent);

	LeftHand = CreateDefaultSubobject<UHandMeshComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(LeftController);
	LeftHand->bIsMirrored = true;

	LeftControllerAim = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftControllerAim"));
	LeftControllerAim->SetTrackingMotionSource(MotionSourceName::LeftAim);
	LeftControllerAim->SetupAttachment(RootComponent);
	
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetTrackingMotionSource(MotionSourceName::Right);
	RightController->bDisplayDeviceModel = false;
	RightController->SetupAttachment(RootComponent);

	RightHand = CreateDefaultSubobject<UHandMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(RightController);

	RightControllerAim = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightControllerAim"));
	RightControllerAim->SetTrackingMotionSource(MotionSourceName::RightAim);
	RightControllerAim->SetupAttachment(RootComponent);
	
	TeleportComponent = CreateDefaultSubobject<UTeleportComponent>(TEXT("TeleportComponent"));
	TeleportComponent->SetupAttachment(RightControllerAim);
}

void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!InputMappingContext)
	{
		UE_LOG(LogInput, Error, TEXT("InputMappingContext is not set up for the player"));
		return;
	}
	
	if (!InputConfig)
	{
		UE_LOG(LogInput, Error, TEXT("InputConfig data asset is not set up for the player"));
		return;
	}

	// add default mapping context
	const APlayerController* PlayerController = GetController<APlayerController>();
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	// set actions up
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInput->BindAction(InputConfig->Move, ETriggerEvent::Triggered, this, &AVRCharacter::Move);
	EnhancedInput->BindAction(InputConfig->Look, ETriggerEvent::Triggered, this, &AVRCharacter::Look);
	EnhancedInput->BindAction(InputConfig->SnapTurn, ETriggerEvent::Triggered, this, &AVRCharacter::SnapTurn);

	EnhancedInput->BindAction(InputConfig->Teleport, ETriggerEvent::Started, this, &AVRCharacter::StartTeleport);
	EnhancedInput->BindAction(InputConfig->Teleport, ETriggerEvent::Completed, this, &AVRCharacter::FinishTeleport);
	EnhancedInput->BindAction(InputConfig->CancelTeleport, ETriggerEvent::Triggered, this, &AVRCharacter::CancelTeleport);

	LeftHand->SetupInput(EnhancedInput, InputConfig, InputSubsystem, EControllerHand::Left);
	RightHand->SetupInput(EnhancedInput, InputConfig, InputSubsystem, EControllerHand::Right);
}

void AVRCharacter::OnUserSettingsChanged()
{
	if (MovementMode != GameUserSettings->GetVRMovementMode())
	{
		if (MovementMode == EVRMovementMode::Blink)
		{
			CancelTeleport();
		}

		MovementMode = GameUserSettings->GetVRMovementMode();
	}
}

void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameUserSettings = Cast<UVRGameUserSettings>(GEngine->GetGameUserSettings());
	if (!GameUserSettings)
	{
		UE_LOG(LogTemp, Error, TEXT("Game user settings is null"));
		return;
	}

	MovementMode = GameUserSettings->GetVRMovementMode();
	
	if (UVRStatics::IsHMDActive())
	{
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
	}

	TeleportComponent->SetArcFXSystem(TeleportFX);
}

void AVRCharacter::Move(const FInputActionInstance& Instance)
{
	if (UVRStatics::IsHMDActive() && MovementMode == EVRMovementMode::Blink)
	{
		return;
	}
	
	const FVector2D Vector = Instance.GetValue().Get<FVector2D>();
	AddMovementInput(GetMovementForwardVector(), Vector.X);
	AddMovementInput(GetMovementRightVector(), Vector.Y);
}

void AVRCharacter::Look(const FInputActionInstance& Instance)
{
	const FVector2D Vector = Instance.GetValue().Get<FVector2D>();
	AddControllerPitchInput(Vector.Y);
	AddControllerYawInput(Vector.X);
}

void AVRCharacter::SnapTurn(const FInputActionInstance& Instance)
{
	const float Value = FMath::Sign(Instance.GetValue().Get<float>());
	AddControllerYawInput(Value * GameUserSettings->GetSnapTurnAngle());
}

void AVRCharacter::StartTeleport()
{
	if (MovementMode != EVRMovementMode::Blink)
	{
		return;
	}
	
	TeleportComponent->StartTeleport();
}

void AVRCharacter::FinishTeleport()
{
	if (MovementMode != EVRMovementMode::Blink)
	{
		return;
	}
	
	TeleportComponent->FinishTeleport();
}

void AVRCharacter::CancelTeleport()
{
	TeleportComponent->CancelTeleport();
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

