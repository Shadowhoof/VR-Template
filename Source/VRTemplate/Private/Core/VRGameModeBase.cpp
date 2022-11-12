// Fill out your copyright notice in the Description page of Project Settings.


#include "VRTemplate/Public/Core/VRGameModeBase.h"

#include "VRTemplate/Public/VRCharacter.h"

AVRGameModeBase::AVRGameModeBase()
{
	DefaultPawnClass = AVRCharacter::StaticClass();
}
