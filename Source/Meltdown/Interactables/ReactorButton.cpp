// Fill out your copyright notice in the Description page of Project Settings.


#include "ReactorButton.h"
#include "Meltdown/Reactor/AReactor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

AReactorButton::AReactorButton() {

    PrimaryActorTick.bCanEverTick = true;

    ButtonLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ButtonLight"));
    ButtonLight->SetupAttachment(Mesh);
    ButtonLight->SetIntensity(1500.f);
    ButtonLight->SetLightColor(FLinearColor::Red);

    ButtonAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ButtonAudio"));
    ButtonAudio->SetupAttachment(RootComponent);

    bIsPressed = false;
    GlowDuration = 1.5f;

}

// Called when the game starts or when spawned
void AReactorButton::BeginPlay() {

    Super::BeginPlay();
    UpdateVisuals();
    
}

void AReactorButton::Interact_Implementation(AActor* Interactor) {

    if (!bIsPressed) {

        ActivateButton();

    }

}

void AReactorButton::ActivateButton() {

    bIsPressed = true;
    UpdateVisuals();

    if (LinkedReactor) {

        LinkedReactor->ApplyCooling(100.f);

    }

    GetWorldTimerManager().SetTimer(GlowResetTimer, this, &AReactorButton::ResetButton, GlowDuration, false);
}

void AReactorButton::ResetButton()
{
    bIsPressed = false;
    UpdateVisuals();
}


void AReactorButton::UpdateVisuals()
{
    if (ButtonLight) {

        if (bIsPressed) {

            ButtonAudio->Play();
            ButtonLight->SetIntensity(5000.f);
            ButtonLight->SetLightColor(FLinearColor::Green);
            SetPromptVisible(false);

        }
        else {

            ButtonAudio->Stop();
            ButtonLight->SetIntensity(1500.f);
            ButtonLight->SetLightColor(FLinearColor::Red);
            SetPromptVisible(true);

        }

    }

}
