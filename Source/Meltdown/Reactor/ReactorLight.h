// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "ReactorLight.generated.h"

UCLASS()
class MELTDOWN_API AReactorLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReactorLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ReactorLight")
	UStaticMeshComponent* LightMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ReactorLight")
	UPointLightComponent* AlarmLight;

	UFUNCTION(BlueprintCallable, Category = "ReactorLight")
	void ChangeColor(FLinearColor Color, float TempRatio);

};
