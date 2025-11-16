#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Meltdown/Reactor/AReactor.h"
#include "ReactorButton.generated.h"

UCLASS()
class MELTDOWN_API AReactorButton : public AInteractableActor
{
    GENERATED_BODY()

public:
    AReactorButton();

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

public:
    virtual void Interact_Implementation(AActor* Interactor) override;
};