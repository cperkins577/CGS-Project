// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Subsystems/WorldSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveComponent.h"
#include "ObjectiveHud.h"
#include "ObjectiveWorldSubsystem.generated.h"

/**
 * 
 */
class UObjectiveComponent;
class UObjectiveHud;
class UUserWidget;
UCLASS()
class MYPROJECT_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:

	//void OnObjectiveCompleted();

	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription();

	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(UObjectiveComponent* Objectivecomponent);

	UFUNCTION(BlueprintCallable)
	void OnMapStart();

protected:

	virtual void Deinitialize();

	void CreateObjectiveWidgets();

	void DisplayObjectiveWidget();
	void RemoveObjectiveWidget();

	void DisplayObjectivesCompletedWidget();
	void RemoveObjectivesCompletedWidget();

	uint32 GetCompletedObjectiveCount();

	void OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState);

private:
	UObjectiveHud* ObjectiveWidget = nullptr;
	UUserWidget* ObjectivesCompletedWidget = nullptr;
	
	TArray<UObjectiveComponent*> Objectives;
};
