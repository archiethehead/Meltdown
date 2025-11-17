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
	// Sets default values for this actor's properties
	AAReactor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
    //Reactor Temperature Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor")
    float CoreTemperature;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor")
    float MaxTemperature;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor")
    float HeatIncreaseRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor")
    float CoolingRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor")
    float StabilityFactor;

    //In Game Variables
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reactor")
    UStaticMeshComponent* CoreMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor")
    TArray<AReactorLight*> ReactorLightArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reactor")
    TArray<AControlRod*> ControlRodArray;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reactor")
    UAudioComponent* ReactorAudio;

    //Methods
    UFUNCTION(BlueprintCallable, Category = "Reactor")
    void ApplyCooling(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Reactor")
    void ApplyUpgrade(float EfficiencyModifier, float StabilityModifier);

private:

    void UpdateReactorVisuals();

    void TriggerMeltdown();

};
