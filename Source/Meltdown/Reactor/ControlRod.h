// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "ControlRod.generated.h"

UCLASS()
class MELTDOWN_API AControlRod : public AActor
{
	GENERATED_BODY()
	
public:	

	//Constructor
	AControlRod();

	//Called Every Frame
	virtual void Tick(float DeltaTime) override;

	//Called On Initialization
	virtual void BeginPlay() override;

	//Control Rod Methods
	UFUNCTION(BlueprintCallable, Category = "ControlRod/Methods")
	float GetModifier() { return Modifier; }

	UFUNCTION(BlueprintCallable, Category = "ControlRod/Methods")
	float GetInsertionDepth() { return InsertionDepth; }

	UFUNCTION(BlueprintCallable, Category = "ControlRod/Methods")
	void ChangeRodDepth(float NewDepth);

	UFUNCTION(BlueprintCallable, Category = "ControlRod/Methods")
	void ToggleJam() { IsJammed = !IsJammed; }

	UFUNCTION(BlueprintCallable, Category = "ControlRod/Methods")
	void ForceFullInsert();

protected:

	void UpdateRodPositionVisual();

	//Unreal Asset Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ControlRod/UnrealAssets")
	UStaticMeshComponent* ControlRodMesh;

	//Control Rod Tunables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ControlRod/Tunable")
	float InsertionDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ControlRod/Tunable")
	float Modifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ControlRod/Tunable")
	float InsertionSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ControlRod/Tunable")
	bool IsJammed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ControlRod/Tunable")
	bool IsForcefullyInserted;

	// animated visual depth (0..1)
	float CurrentVisualDepth = 0.0f;

	// target logical depth (0..1) - your existing InsertionDepth can be the target
	// but if you prefer keep both.
	float TargetInsertionDepth = 0.0f;

	// store the mesh's initial relative Z so movement is consistent
	float InitialMeshRelativeZ = 0.0f;

	// whether we're currently animating
	bool bAnimating = false;

	// how quickly the visual depth approaches the target (tune)
	float VisualLerpSpeed = 2.0f;

};
