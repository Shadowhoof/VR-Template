// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/VRGameModeBase.h"
#include "Core/VRCharacter.h"

AVRGameModeBase::AVRGameModeBase()
{
	DefaultPawnClass = AVRCharacter::StaticClass();
}
