// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HandAnimInstance.generated.h"

/**
 *  Actions that can be applied to a VR hand.
 */
enum class EHandAction : uint8
{
	Grasp,
	IndexCurl,
	IndexPoint,
	ThumbUp,
};


/**
 *  Animation instance used for VR hands.
 */
UCLASS()
class VRTEMPLATE_API UHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	/**
	 * @brief Sets either 0.0 or 1.0 value for the given action based on the provided boolean.
	 * @param Action Action to set the value for
	 * @param Value true will set the value to 1.0, false - to 0.0
	 */
	void SetHandAction(EHandAction Action, bool Value);
	
	void SetHandAction(EHandAction Action, float Value);

	void SetIsMirrored(bool bMirror);
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	float Grasp = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	float IndexCurl = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	float IndexPoint = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	float ThumbUp = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	bool bIsMirrored = false;
};
