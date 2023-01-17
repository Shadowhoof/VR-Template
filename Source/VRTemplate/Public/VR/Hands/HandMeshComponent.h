// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HandMeshComponent.generated.h"

struct FInputActionValue;
class UHandAnimInstance;
class UInputConfig;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VRTEMPLATE_API UHandMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	
	UHandMeshComponent();
	
	void SetupInput(UEnhancedInputComponent* InputComponent, UInputConfig* InputConfig,
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem, EControllerHand Hand);	

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	bool bIsMirrored = false;
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
protected:

	virtual void BeginPlay() override;
	
	void OnHandGraspTriggered(const FInputActionValue& Value);
	void OnHandGraspReleased();

	void OnIndexFingerCurlTriggered(const FInputActionValue& Value);
	void OnIndexFingerCurlReleased();
	
	void OnIndexFingerPointTriggered();
	void OnIndexFingerPointReleased();
	
	void OnThumbUpTriggered();
	void OnThumbUpReleased();

private:

	UPROPERTY()
	TObjectPtr<UHandAnimInstance> HandAnimInstance;

};
