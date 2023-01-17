// Fill out your copyright notice in the Description page of Project Settings.


#include "VR/Hands/HandMeshComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/InputConfig.h"
#include "VR/Hands/HandAnimInstance.h"


UHandMeshComponent::UHandMeshComponent()
{
	AnimClass = UHandAnimInstance::StaticClass();
}

void UHandMeshComponent::SetupInput(UEnhancedInputComponent* InputComponent, UInputConfig* InputConfig,
                                    UEnhancedInputLocalPlayerSubsystem* InputSubsystem, EControllerHand Hand)
{
	if (!InputMappingContext)
	{
		UE_LOG(LogInput, Error, TEXT("No InputMappingContext specified for HandMeshComponent"));
		return;
	}

	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	const UInputAction* GraspAction = Hand == EControllerHand::Left ? InputConfig->HandGraspLeft : InputConfig->HandGraspRight;
	InputComponent->BindAction(GraspAction, ETriggerEvent::Triggered, this, &UHandMeshComponent::OnHandGraspTriggered);
	InputComponent->BindAction(GraspAction, ETriggerEvent::Completed, this, &UHandMeshComponent::OnHandGraspReleased);

	const UInputAction* IndexCurlAction = Hand == EControllerHand::Left ? InputConfig->IndexFingerCurlLeft : InputConfig->IndexFingerCurlRight;
	InputComponent->BindAction(IndexCurlAction, ETriggerEvent::Triggered, this, &UHandMeshComponent::OnIndexFingerCurlTriggered);
	InputComponent->BindAction(IndexCurlAction, ETriggerEvent::Completed, this, &UHandMeshComponent::OnIndexFingerCurlReleased);

	const UInputAction* IndexPointAction = Hand == EControllerHand::Left ? InputConfig->IndexFingerPointLeft : InputConfig->IndexFingerPointRight;
	InputComponent->BindAction(IndexPointAction, ETriggerEvent::Triggered, this, &UHandMeshComponent::OnIndexFingerPointTriggered);
	InputComponent->BindAction(IndexPointAction, ETriggerEvent::Completed, this, &UHandMeshComponent::OnIndexFingerPointReleased);

	const UInputAction* ThumbUpAction = Hand == EControllerHand::Left ? InputConfig->ThumbUpLeft : InputConfig->ThumbUpRight;
	InputComponent->BindAction(ThumbUpAction, ETriggerEvent::Triggered, this, &UHandMeshComponent::OnThumbUpTriggered);
	InputComponent->BindAction(ThumbUpAction, ETriggerEvent::Completed, this, &UHandMeshComponent::OnThumbUpReleased);
}

void UHandMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	HandAnimInstance = Cast<UHandAnimInstance>(GetAnimInstance());
	HandAnimInstance->SetIsMirrored(bIsMirrored);
}

void UHandMeshComponent::OnHandGraspTriggered(const FInputActionValue& Value)
{
	const float FloatValue = Value.Get<float>();
	HandAnimInstance->SetHandAction(EHandAction::Grasp, FloatValue);
}

void UHandMeshComponent::OnHandGraspReleased()
{
	HandAnimInstance->SetHandAction(EHandAction::Grasp, false);
}

void UHandMeshComponent::OnIndexFingerCurlTriggered(const FInputActionValue& Value)
{
	const float FloatValue = Value.Get<float>();
	HandAnimInstance->SetHandAction(EHandAction::IndexCurl, FloatValue);
}

void UHandMeshComponent::OnIndexFingerCurlReleased()
{
	HandAnimInstance->SetHandAction(EHandAction::IndexCurl, false);
}

void UHandMeshComponent::OnIndexFingerPointTriggered()
{
	HandAnimInstance->SetHandAction(EHandAction::IndexPoint, false);
}

void UHandMeshComponent::OnIndexFingerPointReleased()
{
	HandAnimInstance->SetHandAction(EHandAction::IndexPoint, true);
}

void UHandMeshComponent::OnThumbUpTriggered()
{
	HandAnimInstance->SetHandAction(EHandAction::ThumbUp, false);
}

void UHandMeshComponent::OnThumbUpReleased()
{
	HandAnimInstance->SetHandAction(EHandAction::ThumbUp, true);
}