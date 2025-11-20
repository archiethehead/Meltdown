// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlRod.h"

// Sets default values
AControlRod::AControlRod()
{

	PrimaryActorTick.bCanEverTick = false;

	//Control Rod Tunable Variables
	InsertionDepth = 0.0f;
	InsertionSpeed = 0.5f;
	Modifier = 0.25;
	IsJammed = false;
	IsForcefullyInserted = false;

	//Components
	ControlRodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RodMesh"));
	RootComponent = ControlRodMesh;



}

// Called when the game starts or when spawned
void AControlRod::BeginPlay()
{
	Super::BeginPlay();

	UpdateRodPositionVisual();
	if (ControlRodMesh)
	{
		InitialMeshRelativeZ = ControlRodMesh->GetRelativeLocation().Z;
	}

	// initialize visual depth to logical depth so rod starts in correct place
	CurrentVisualDepth = InsertionDepth;
	TargetInsertionDepth = InsertionDepth;
	bAnimating = false;
	SetActorTickEnabled(false);
	
}

// Called every frame
void AControlRod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bAnimating)
		return;

	// Smoothly move CurrentVisualDepth toward TargetInsertionDepth
	CurrentVisualDepth = FMath::FInterpTo(CurrentVisualDepth, TargetInsertionDepth, DeltaTime, VisualLerpSpeed);

	// Update the mesh position based on CurrentVisualDepth
	UpdateRodPositionVisual();

	// stop animating when very close
	if (FMath::IsNearlyEqual(CurrentVisualDepth, TargetInsertionDepth, 0.001f))
	{
		CurrentVisualDepth = TargetInsertionDepth;
		UpdateRodPositionVisual(); // final snap (tiny)
		bAnimating = false;
		SetActorTickEnabled(false); // stop ticking to save perf
	}

}

void AControlRod::ForceFullInsert() {

	ChangeRodDepth(1.0);
	VisualLerpSpeed = 10.0f;

}

void AControlRod::ChangeRodDepth(float NewDepth) {

	if (IsJammed || IsForcefullyInserted) return;

	// NewDepth is an absolute 0..1 target
	TargetInsertionDepth = FMath::Clamp(NewDepth, 0.0f, 1.0f);

	// If you keep InsertionDepth as the logical (authoritative) value:
	InsertionDepth = TargetInsertionDepth;

	// start animating
	bAnimating = true;
	SetActorTickEnabled(true); // enable Tick so we animate every frame

	if (InsertionDepth == 0.0f) VisualLerpSpeed = 0.5f;
	else VisualLerpSpeed = 2.0f;


}

void AControlRod::UpdateRodPositionVisual() {

	if (!ControlRodMesh) return;

	// Travel distance in world units (tweak to match your mesh)
	const float TravelDistance = 450.0f;

	// Compute Z offset relative to initial mesh Z
	float ZOffset = InitialMeshRelativeZ + (-CurrentVisualDepth * TravelDistance);

	// Get current relative transform and only change Z
	FVector Rel = ControlRodMesh->GetRelativeLocation();
	Rel.Z = ZOffset;
	ControlRodMesh->SetRelativeLocation(Rel);

}