// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReactorLight.h"
#include "ControlRod.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "AReactor.generated.h"


UCLASS()
class MELTDOWN_API AAReactor : public AActor {
	GENERATED_BODY()
	
public:

    // Constructor
    AAReactor();

    //Called Every Frame
    virtual void Tick(float DeltaTime) override;

    //Called On Initialization
    virtual void BeginPlay() override;

    //Reactor State Variables
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reactor/State")
    float TotalControlRodModifier;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reactor/State")
    float CoreTemperature;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reactor/State")
    float CoolantTemperature;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reactor/State")
    float CoolantAmount;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reactor/State")
    bool IsPumpOn;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reactor/State")
    bool IsMeltdown;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reactor/State")
    bool IsExploded;

    //Reactor Tunable Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin="0.0"))
    float BaseHeatPerSecond;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin = "0.0", ClampMax= "1.0"))
    float RodMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin = "0.0"))
    float MaxCoolingPerSecond;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin = "0.0"))
    float PassiveCoolingPerSecond;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin = "1.0"))
    float MaxCoolantAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin = "0.0"))
    float CoolantBoilingLossRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin = "0.0"))
    float CoolantBoilingPoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin = "0.0"))
    float SCRAMImmediateCool;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin = "0.0"))
    float SCRAMTempFailureThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float SCRAMCoolantFailureThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin = "0.0"))
    float MeltdownThreshold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/Tunable", meta = (ClampMin = "0.0"))
    float ExplosionThreshold;

    //Reactor Methods
    UFUNCTION(BlueprintCallable, Category = "Reactor/Methods")
    void PumpToggle();

    UFUNCTION(BlueprintCallable, Category = "Reactor/Methods")
    void SCRAM();

protected:

    //Unreal Asset Variables
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reactor/UnrealAssets")
    UStaticMeshComponent* CoreMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reactor/UnrealAssets")
    UAudioComponent* ReactorAudio;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/UnrealAssets")
    TArray<AReactorLight*> ReactorLightArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor/UnrealAssets")
    TArray<AControlRod*> ControlRodArray;

    //Reactor Methods
    void ComputeTotalControlRodModifier();

    void CalculateTemperature(float DeltaTime);

    void CheckFailure();

    float ClampNum(float v) {

        return FMath::Clamp(v, 0.0, 1.0);

    }

    void UpdateReactorVisuals();

    void TriggerMeltdown();

    void TriggerExplosion();

};
