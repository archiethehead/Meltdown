// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Meltdown/Interactables/Interactable.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DrawDebugHelpers.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MELTDOWN_API APlayerCharacter : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Input callback functions
	void MoveForward(const FInputActionValue& Value);
	void MoveSideways(const FInputActionValue& Value);

	void LookPitch(const FInputActionValue& Value);
	void LookYaw(const FInputActionValue& Value);

	void Jumping();

	void Interact();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveXAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveYAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookPitchAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookYawAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractAction;

};