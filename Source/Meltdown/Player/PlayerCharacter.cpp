// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Meltdown/Interactables/Interactable.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter() {

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Third Person Camera Logic
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Create Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(GetMesh(), TEXT("head"));
	FollowCamera->bUsePawnControlRotation = true;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay() {

	Super::BeginPlay();
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	if (APlayerController* PC = Cast<APlayerController>(GetController())) {

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {

			if (PlayerMappingContext) {

				Subsystem->AddMappingContext(PlayerMappingContext, 0);

			}

		}

	}
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInput->BindAction(MoveXAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
		EnhancedInput->BindAction(MoveYAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveSideways);

		EnhancedInput->BindAction(LookPitchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookPitch);
		EnhancedInput->BindAction(LookYawAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LookYaw);

		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jumping);

		EnhancedInput->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);

	}

}

void APlayerCharacter::MoveForward(const FInputActionValue& Value) {

	if (Controller != nullptr) {


		const float AxisValue = Value.Get<float>();
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDir, AxisValue);


	}

}

void APlayerCharacter::MoveSideways(const FInputActionValue& Value) {

	if (Controller != nullptr) {

		const float AxisValue = Value.Get<float>();
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(RightDir, AxisValue);

	}

}

void APlayerCharacter::LookPitch(const FInputActionValue& Value) {

	const float AxisValue = Value.Get<float>();
	AddControllerPitchInput(AxisValue);

}

void APlayerCharacter::LookYaw(const FInputActionValue& Value) {

	const float AxisValue = Value.Get<float>();
	AddControllerYawInput(AxisValue);

}

void APlayerCharacter::Jumping() {

	Super::Jump();

}

void APlayerCharacter::Interact() {

	FVector Start = FollowCamera->GetComponentLocation();
	FVector End = Start + (FollowCamera->GetForwardVector() * 300.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params)) {

		AActor* HitActor = Hit.GetActor();
		if (HitActor && HitActor->Implements<UInteractable>()) {

			IInteractable::Execute_Interact(HitActor, this);

		}
	}
}