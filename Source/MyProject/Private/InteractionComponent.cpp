// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "MyProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCaspule"));

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::OnOverlapEnd);

	InteractingActor = nullptr;
}


void UInteractionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* Othercomp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("UInteractionComponent::OnOverlapBegin"));
	if (OtherActor->ActorHasTag("Player"))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Overlapping Player"));
		InteractingActor = OtherActor;
	}
}

void UInteractionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("UInteractionComponent::OnOverlapEnd"));
	InteractingActor = nullptr;
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AMyProjectCharacter* Player = Cast<AMyProjectCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		Player->OnInteractionStart.AddUObject(this, &UInteractionComponent::InteractionStart);
	}
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (InteractingActor)
	{
		FVector Offset(0.0f, 0.0f, 100.0f);
		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;
		DrawDebugString(GetWorld(), Offset, InteractionPrompt.ToString(), GetOwner(), FColor::Blue, 0.0f);
	}
	// ...
}

void UInteractionComponent::InteractionStart()
{
	//UE_LOG(LogTemp, Warning, TEXT("Interaction Starting"));
}