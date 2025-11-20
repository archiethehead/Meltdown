// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Meltdown/Reactor/ControlRod.h"
#include "InteractableActor.h"
#include "Components/PointLightComponent.h"
#include "ControlRodValve.generated.h"

UCLASS()
class MELTDOWN_API AControlRodValve : public AInteractableActor
{
	GENERATED_BODY()

public:

	AControlRodValve();
	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Reactor")
    AControlRod* LinkedControlRod;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ControlRodValve/State")
    bool IsTurning;

    UPROPERTY(EditAnywhere, Category = "Button")
    float TurnDuration;

    FTimerHandle GlowResetTimer;

    float ValveTurn = 0.0f;

    void ActivateValve();
    void ResetValve();
    void UpdateVisuals();
	
};
