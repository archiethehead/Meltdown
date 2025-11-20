// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlRodValve.h"

AControlRodValve::AControlRodValve() {

	PrimaryActorTick.bCanEverTick = false;

    ValveTurn = 0.0f;
    IsTurning = false;
    TurnDuration = 1.5f;

}

void AControlRodValve::BeginPlay() {

    Super::BeginPlay();
    UpdateVisuals();

}

void AControlRodValve::Interact_Implementation(AActor* Interactor) {

    if (!IsTurning) {
    
        ActivateValve();
    
    }

}

void AControlRodValve::ActivateValve() {

    IsTurning = true;
    UpdateVisuals();

    if (LinkedControlRod) {
    
        if (ValveTurn == 1.0f) { 

            ValveTurn = 0.0f;

        }

        else {
        
            ValveTurn += 0.25f;

        }

        LinkedControlRod->ChangeRodDepth(ValveTurn);
    
    }

    GetWorldTimerManager().SetTimer(GlowResetTimer, this, &AControlRodValve::ResetValve, TurnDuration, false);

}

void AControlRodValve::ResetValve() {

    IsTurning = false;
    UpdateVisuals();

}

void AControlRodValve::UpdateVisuals() {

    if (IsTurning) {
    
        SetPromptVisible(false);

    }

    else {
    
        SetPromptVisible(true);

    }

}