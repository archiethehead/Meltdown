// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Meltdown/Player/PlayerCharacter.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->SetupAttachment(RootComponent);
    InteractionSphere->SetSphereRadius(200.f);
    InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractableActor::OnOverlapBegin);
    InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AInteractableActor::OnOverlapEnd);

    PromptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PromptWidget"));
    PromptWidget->SetupAttachment(RootComponent);
    PromptWidget->SetWidgetSpace(EWidgetSpace::Screen);
    PromptWidget->SetDrawSize(FVector2D(150, 50));
    PromptWidget->SetVisibility(false);

}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActor::Interact_Implementation(AActor* Interactor) {



}


void AInteractableActor::OnEnterRange_Implementation(AActor* Interactor) {

    SetPromptVisible(true);

}

void AInteractableActor::OnExitRange_Implementation(AActor* Interactor) {

    SetPromptVisible(false);

}

void AInteractableActor::SetPromptVisible(bool bVisible) {

    if (PromptWidget) {

        PromptWidget->SetVisibility(bVisible, false);

    }

}

void AInteractableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

    if (OtherActor && OtherActor != this && OtherActor->ActorHasTag(TEXT("Player"))) {

        IInteractable::Execute_OnEnterRange(this, OtherActor);

    }

}

void AInteractableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

    if (OtherActor && OtherActor != this && OtherActor->ActorHasTag(TEXT("Player"))) {

        IInteractable::Execute_OnExitRange(this, OtherActor);

    }

}