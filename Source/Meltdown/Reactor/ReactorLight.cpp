// Fill out your copyright notice in the Description page of Project Settings.


#include "ReactorLight.h"

// Sets default values
AReactorLight::AReactorLight()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    AlarmLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("AlarmLight"));
    AlarmLight->SetupAttachment(RootComponent);

    LightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
    LightMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AReactorLight::BeginPlay()
{
    Super::BeginPlay();
    
}

void AReactorLight::ChangeColor(FLinearColor Color, float TempRatio) {
       
    AlarmLight->SetLightColor(Color);
    AlarmLight->SetIntensity(FMath::Lerp(500.f, 300.f, TempRatio));

}