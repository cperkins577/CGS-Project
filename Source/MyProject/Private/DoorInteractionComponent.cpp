// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation = GetOwner()->GetActorRotation();
	StartRotation = GetOwner()->GetActorRotation();
	//FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;

	CurrentRotationTime = 0.0f;
	// ...
	
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentRotationTime < TimeToRotate)
	{
		if ((ATriggerBox1 || ATriggerBox2) && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && (ATriggerBox1->IsOverlappingActor(PlayerPawn) || ATriggerBox2->IsOverlappingActor(PlayerPawn))) {

				if (ATriggerBox1->IsOverlappingActor(PlayerPawn) && IsDoorClosed)
				{
					FinalRotation = OriginalRotation + DesiredRotation;
					CurrentRotationTime += DeltaTime;
					const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
					const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
					const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
					GetOwner()->SetActorRotation(CurrentRotation);
					if (CurrentRotation == FinalRotation) {
						IsDoorClosed = false;
						StartRotation = GetOwner()->GetActorRotation();
						FinalRotation = OriginalRotation;
						CurrentRotationTime = 0.0f;
					}
				}
				if (ATriggerBox2->IsOverlappingActor(PlayerPawn) && IsDoorClosed)
				{
					FinalRotation = OriginalRotation - DesiredRotation;
					CurrentRotationTime += DeltaTime;
					const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
					const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
					const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
					GetOwner()->SetActorRotation(CurrentRotation);
					if (CurrentRotation == FinalRotation) {
						IsDoorClosed = false;
						StartRotation = GetOwner()->GetActorRotation();
						FinalRotation = OriginalRotation;
						CurrentRotationTime = 0.0f;
					}
				}
			}
			if (PlayerPawn && !ATriggerBox1->IsOverlappingActor(PlayerPawn) && !ATriggerBox2->IsOverlappingActor(PlayerPawn) && !IsDoorClosed)
			{
				CurrentRotationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
				if (CurrentRotation == FinalRotation) {
					IsDoorClosed = true;
					StartRotation = GetOwner()->GetActorRotation();
					FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
					CurrentRotationTime = 0.0f;
				}
			}
		}

	}
	// ...
}

