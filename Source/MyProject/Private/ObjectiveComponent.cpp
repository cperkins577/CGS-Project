// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveComponent.h"
#include "ObjectiveWorldSubsystem.h"

// Sets default values for this component's properties
UObjectiveComponent::UObjectiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
	State = EObjectiveState::OS_Inactive;

	// ...
}

void UObjectiveComponent::SetState(EObjectiveState NewState)
{
	if (NewState != State)
	{
		State = NewState;
		StateChangedEvent.Broadcast(this, State);
	}
}

void UObjectiveComponent::InitializeComponent()
{
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->AddObjective(this);
	}
}


//// Called when the game starts
//void UObjectiveComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
//	if (ObjectiveWorldSubsystem)
//	{
//		ObjectiveWorldSubsystem->AddObjective(this);
//	}
//}

void UObjectiveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->RemoveObjective(this);
	}
	Super::EndPlay(EndPlayReason);
}


/*// Called every frame
void UObjectiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/

