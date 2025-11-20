// Fill out your copyright notice in the Description page of Project Settings.


#include "AReactor.h"

// Sets default values
AAReactor::AAReactor() {
	
	PrimaryActorTick.bCanEverTick = true;

	//Reactor State Variables
	TotalControlRodModifier = 0.0f;
	CoreTemperature = 300.0f;
	CoolantTemperature = 280.0f;
	MaxCoolantAmount = 100.0f;
	CoolantAmount = MaxCoolantAmount;
	IsPumpOn = false;
	IsMeltdown = false;
	IsExploded = false;

	//Reactor Tunable Variables
	BaseHeatPerSecond = 40.0f;
	RodMultiplier = 1.0f;
	MaxCoolingPerSecond = 60.0f;
	PassiveCoolingPerSecond = 1.5f;
	CoolantBoilingLossRate = 2.0f;
	CoolantBoilingPoint = 600.0f;
	SCRAMImmediateCool = 50.0f;
	SCRAMTempFailureThreshold = 900.0f;
	SCRAMCoolantFailureThreshold = 0.15f;
	MeltdownThreshold = 1000.0f;
	ExplosionThreshold = 1400.0f;

	//Components
	CoreMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoreMesh"));
	CoreMesh->SetupAttachment(RootComponent);
	RootComponent = CoreMesh;

	ReactorAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ReactorAudio"));
	ReactorAudio->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAReactor::BeginPlay() {

	Super::BeginPlay();

	ReactorAudio->Play();
	
}

// Called every frame
void AAReactor::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (IsExploded) return;

	ComputeTotalControlRodModifier();

	CalculateTemperature(DeltaTime);

	CheckFailure();

	UpdateReactorVisuals();

}

void AAReactor::ComputeTotalControlRodModifier() {

	float TotalModifier = 0.f;
	for (int x = 0; x < ControlRodArray.Num(); x++) {
	
		TotalModifier += ControlRodArray[x]->GetInsertionDepth() * ControlRodArray[x]->GetModifier();
	
	}

	TotalControlRodModifier = ClampNum(TotalModifier);

}

void AAReactor::CalculateTemperature(float DeltaTime) {


	//Control Rod Contribution
	float Heat = BaseHeatPerSecond * (1.0 - (TotalControlRodModifier * RodMultiplier));

	//Coolant Contribution
	float CoolantFraction = (MaxCoolantAmount > 0.0f) ? (CoolantAmount / MaxCoolantAmount) : 0.0f;
	CoolantFraction = ClampNum(CoolantFraction);

	float CurrentCooling = 0.0f;
	if (IsPumpOn && CoolantFraction > 0.0f) CurrentCooling = MaxCoolingPerSecond * CoolantFraction;
	else CurrentCooling = (MaxCoolingPerSecond * 0.25f) * CoolantFraction;

	//Core and Coolant Heating
	CoreTemperature += (Heat - CurrentCooling - PassiveCoolingPerSecond) * DeltaTime;
	CoolantTemperature += (CoreTemperature - CoolantTemperature) * 0.02f * DeltaTime;
	
	//Coolant Loss Calculation (If Boiling)
	if (CoolantTemperature > CoolantBoilingPoint) {
	
		float CoolantLoss = CoolantBoilingLossRate * 
		((CoolantTemperature - CoolantBoilingPoint) / 100.0f) * DeltaTime;
		CoolantAmount = FMath::Max(0.0f, CoolantAmount - CoolantLoss);
	
	}

	//Temperature Cap
	CoreTemperature = FMath::Clamp(CoreTemperature, -100.0f, 5000.0f);
	CoolantTemperature = FMath::Clamp(CoolantTemperature, -100.0f, 5000.0f);

}

void AAReactor::PumpToggle() { 

	IsPumpOn = !IsPumpOn; 

}

void AAReactor::CheckFailure() {

	if (!IsMeltdown && CoreTemperature >= MeltdownThreshold) {
	
		IsMeltdown = true;
		TriggerMeltdown();
	
	}

	if (!IsExploded && CoreTemperature >= ExplosionThreshold) {

		IsExploded = true;
		TriggerExplosion();

	}

}

void AAReactor::SCRAM() {

	for (int x = 0; x < ControlRodArray.Num(); x++) {
	
		ControlRodArray[x]->ForceFullInsert();
	
	}

	ComputeTotalControlRodModifier();
	CoreTemperature = FMath::Max(0.0f, CoreTemperature - SCRAMImmediateCool);
	float CoolantFraction = (MaxCoolantAmount > 0.0f) ? (CoolantAmount / MaxCoolantAmount) : 0.0f;

	if (CoolantTemperature > SCRAMCoolantFailureThreshold && CoolantFraction < SCRAMCoolantFailureThreshold) {
	
		if (FMath::FRand() < 0.75f) {
		
			IsExploded = true;
			return;
		
		}

		else {
		
			for (int x = 0; x < ControlRodArray.Num(); x++) {

				if (FMath::FRand() < 0.35f) {
				
					ControlRodArray[x]->ToggleJam();

				}

			}
			ComputeTotalControlRodModifier();
		
		}
	
	}


}

void AAReactor::UpdateReactorVisuals() {

	if (!ReactorLightArray[0]) return;

	FLinearColor LightColor = FLinearColor::Green;
	float TempRatio = CoreTemperature / MeltdownThreshold;

	if (TempRatio > 0.7f) {
	
		LightColor = FLinearColor::Red;
	
	}

	else if (TempRatio > 0.4f) {
	
		LightColor = FLinearColor::Yellow;
	
	}

	for (int x = 0; x < ReactorLightArray.Num(); x++) {

		ReactorLightArray[x]->ChangeColor(LightColor, TempRatio);
	
	}

}

void AAReactor::TriggerMeltdown() {

	UE_LOG(LogTemp, Warning, TEXT("HOW DOES AN RBMK REACTOR MELTDOWN?"));

}

void AAReactor::TriggerExplosion() {

	UE_LOG(LogTemp, Warning, TEXT("HOW DOES AN RBMK REACTOR EXPLODE?"));

}