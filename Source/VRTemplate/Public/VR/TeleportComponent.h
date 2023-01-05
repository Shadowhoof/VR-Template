// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TeleportComponent.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VRTEMPLATE_API UTeleportComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UTeleportComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetArcFXSystem(TObjectPtr<UNiagaraSystem> System);

	void StartTeleport();
	void FinishTeleport();
	void CancelTeleport();
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX")
	TSubclassOf<AActor> GroundFXClass;

private:

	UPROPERTY()
	TWeakObjectPtr<UNiagaraSystem> ArcFXSystem;

	UPROPERTY()
	TObjectPtr<AActor> GroundFXActor;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ArcFXComponent;

	bool bIsValidTeleportLocation = false;

private:

	void ResetTeleport();
	
};
