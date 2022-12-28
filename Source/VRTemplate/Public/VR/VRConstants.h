#pragma once

UENUM(BlueprintType)
enum class EVRMovementMode : uint8
{
	/* Movement is performed by teleporting a short distance. */
	Blink,

	/* Smooth movement in the direction the head is facing. */
	ContinuousHead,

	/* Smooth movement in the direction motion controllers are facing. */
	ContinuousControllers,
};