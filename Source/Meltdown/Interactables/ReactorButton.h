#pragma once

#include "CoreMinimal.h"
#include "Meltdown/Reactor/AReactor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "InteractableActor.h"
#include "ReactorButton.generated.h"

UCLASS()
class MELTDOWN_API AReactorButton : public AInteractableActor
{
    GENERATED_BODY()

public:
    AReactorButton();
    virtual void Interact_Implementation(AActor* Interactor) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "Button")
    UPointLightComponent* ButtonLight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reactor")
    UAudioComponent* ButtonAudio;

    UPROPERTY(EditAnywhere, Category = "Reactor")
    AAReactor* LinkedReactor;

    bool bIsPressed;

    UPROPERTY(EditAnywhere, Category = "Button")
    float GlowDuration;

    FTimerHandle GlowResetTimer;

    void ActivateButton();
    void ResetButton();
    void UpdateVisuals();

};