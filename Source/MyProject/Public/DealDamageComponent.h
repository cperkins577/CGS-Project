// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "DealDamageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UDealDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDealDamageComponent();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UCapsuleComponent* GetTriggerCapsule() { return TriggerCapsule; }

	bool IsActive() const { return bActive; }
	void SetActive(bool IsActive) { bActive = IsActive; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float BaseDamage = 50.0f;

	UPROPERTY(EditAnywhere)
	float DamageTotalTime = 2.0f;

	UPROPERTY(EditAnywhere)
	float TakeDamageInterval = 0.5f;

	UPROPERTY(EditAnywhere, NoClear)
	UCapsuleComponent* TriggerCapsule;

	bool bActive = true;

/*
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	*/
		
};
