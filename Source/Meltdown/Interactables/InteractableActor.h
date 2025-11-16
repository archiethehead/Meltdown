// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "InteractableActor.generated.h"

UCLASS()
class MELTDOWN_API AInteractableActor : public AActor, public IInteractable {

	GENERATED_BODY()
	
public:	

	AInteractableActor();

protected:

	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
    USphereComponent* InteractionSphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
    UWidgetComponent* PromptWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
    UStaticMeshComponent* Mesh;

    void SetPromptVisible(bool bVisible);

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual void OnEnterRange_Implementation(AActor* Interactor) override;
    virtual void OnExitRange_Implementation(AActor* Interactor) override;

private:

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
