// Fill out your copyright notice in the Description page of Project Settings.


#include "AReactor.h"

// Sets default values
AAReactor::AAReactor() {
	
	PrimaryActorTick.bCanEverTick = true;


	//Components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	CoreMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoreMesh"));
	CoreMesh->SetupAttachment(RootComponent);

	ReactorAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ReactorAudio"));
	ReactorAudio->SetupAttachment(RootComponent);

	//Defaults
	CoreTemperature = 25.f;
	MaxTemperature = 100.f;
	HeatIncreaseRate = 5.f;
	CoolingRate = 15.f;
	StabilityFactor = 1.f;

}

// Called when the game starts or when spawned
void AAReactor::BeginPlay() {
	Super::BeginPlay();

	if (ReactorAudio && !ReactorAudio ->IsPlaying()) {

		ReactorAudio->Play();

	}
	
}

// Called every frame
void AAReactor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//Temperature System
	CoreTemperature += HeatIncreaseRate * DeltaTime / StabilityFactor;

	//ClampTemperature
	CoreTemperature = FMath::Clamp(CoreTemperature, 0.f, MaxTemperature);
	
	//Check For Meltdown
	if (CoreTemperature >= MaxTemperature) {
	
		TriggerMeltdown();
		
	}

	UpdateReactorVisuals();

}

void AAReactor::ApplyCooling(float Amount) {

	CoreTemperature -= Amount;
	CoreTemperature = FMath::Max(CoreTemperature, 0.f);
	UpdateReactorVisuals();

}

void AAReactor::ApplyUpgrade(float EfficiencyModifier, float StabilityModifier) {

	CoolingRate *= EfficiencyModifier;
	StabilityFactor *= StabilityModifier;

}

void AAReactor::UpdateReactorVisuals() {
	UE_LOG(LogTemp, Log, TEXT("Changing Colour"));
	//Light Temperature Color

	if (!ReactorLightArray[0]) return;

	FLinearColor LightColor = FLinearColor::Green;
	float TempRatio = CoreTemperature / MaxTemperature;

	if (TempRatio > 0.7f) {
	
		LightColor = FLinearColor::Red;
	
	}

	else if (TempRatio > 0.4f) {
	
		LightColor = FLinearColor::Yellow;
	
	}

	for (int x = 0; x < ReactorLightArray.Num(); x++) {

		UE_LOG(LogTemp, Log, TEXT("Colour Changed"));
		ReactorLightArray[x]->ChangeColor(LightColor, TempRatio);
	
	}

}

void AAReactor::TriggerMeltdown() {

	UE_LOG(LogTemp, Warning, TEXT("HOW DOES AN RBMK REACTOR EXPLODE?"));
	CoreTemperature = MaxTemperature;

}