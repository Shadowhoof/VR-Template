#include "VR/TeleportComponent.h"

#include "NavigationSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"


namespace TeleportConstants
{
	const float Radius = 5.f;
	const float Speed = 750.f;
	const float MaxTime = 2.f;

	const FName ArcPointArray = "User.PointArray";
}


UTeleportComponent::UTeleportComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UTeleportComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ArcFXComponent && !GroundFXActor)
	{
		return;
	}

	const FVector Location = GetComponentLocation();
	FPredictProjectilePathParams PredictParams {TeleportConstants::Radius, Location,
		GetForwardVector() * TeleportConstants::Speed, TeleportConstants::MaxTime,
		ECC_WorldStatic, GetOwner()};

	FPredictProjectilePathResult PredictResult;
	UGameplayStatics::PredictProjectilePath(GetWorld(), PredictParams, PredictResult);

	if (ArcFXComponent)
	{
		TArray<FVector> PointArray;
		for (const auto& PathPoint : PredictResult.PathData)
		{
			PointArray.Add(PathPoint.Location);
		}
		UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(ArcFXComponent, TeleportConstants::ArcPointArray, PointArray);
	}
	
	if (GroundFXActor)
	{
		bool bIsPointValid = PredictResult.HitResult.IsValidBlockingHit();
		if (bIsPointValid)
		{
			UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
			if (FNavLocation NavLocation; NavSystem->ProjectPointToNavigation(PredictResult.HitResult.Location, NavLocation))
			{
				GroundFXActor->SetActorLocation(NavLocation.Location);
				GroundFXActor->SetActorRotation((NavLocation.Location - Location).GetSafeNormal2D().Rotation());
			}
		}

		GroundFXActor->GetRootComponent()->SetVisibility(bIsPointValid, true);
		bIsValidTeleportLocation = bIsPointValid;
	}
}

void UTeleportComponent::SetArcFXSystem(TObjectPtr<UNiagaraSystem> System)
{
	ArcFXSystem = System;
}

void UTeleportComponent::StartTeleport()
{
	Activate(false);

	if (GroundFXClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GroundFXActor = GetWorld()->SpawnActor<AActor>(GroundFXClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	}

	if (ArcFXSystem.IsValid())
	{
		ArcFXComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(ArcFXSystem.Get(), this, NAME_None,
			FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false);
	}
}

void UTeleportComponent::FinishTeleport()
{
	if (bIsValidTeleportLocation)
	{
		GetOwner()->TeleportTo(GroundFXActor->GetActorLocation(), GetOwner()->GetActorRotation());
	}
	
	ResetTeleport();
}

void UTeleportComponent::CancelTeleport()
{
	ResetTeleport();
}

void UTeleportComponent::ResetTeleport()
{
	if (!IsActive())
	{
		return;
	}
	
	Deactivate();

	bIsValidTeleportLocation = false;

	if (ArcFXComponent)
	{
		ArcFXComponent->DestroyInstance();
	}
	
	if (GroundFXActor)
	{
		GroundFXActor->Destroy();
		GroundFXActor = nullptr;
	}
}

