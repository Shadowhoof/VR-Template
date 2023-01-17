// Fill out your copyright notice in the Description page of Project Settings.


#include "VR/Hands/HandAnimInstance.h"

void UHandAnimInstance::SetHandAction(EHandAction Action, bool Value)
{
	SetHandAction(Action, Value ? 1.f : 0.f);
}

void UHandAnimInstance::SetHandAction(EHandAction Action, float Value)
{
	switch(Action)
	{
	case EHandAction::Grasp:
		UE_LOG(LogTemp, Log, TEXT("Set grasp value: %.2f, ID: %d"), Value, GetUniqueID());
		Grasp = Value;
		break;
	case EHandAction::IndexCurl:
		IndexCurl = Value;
		break;
	case EHandAction::IndexPoint:
		IndexPoint = Value;
		break;
	case EHandAction::ThumbUp:
		ThumbUp = Value;
		break;
	default:
		break;
	}
}

void UHandAnimInstance::SetIsMirrored(bool bMirror)
{
	bIsMirrored = bMirror;
}
