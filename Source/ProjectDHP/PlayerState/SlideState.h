// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "Components/CapsuleComponent.h"
#include "SlideState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDHP_API USlideState : public UBaseState
{
	GENERATED_BODY()
private:
	UCapsuleComponent* _capsule;
public:
	USlideState();
	USlideState* Init(ADHPCharacter* character, UStateControllerComponent* stateController);
	void EnterState() override;
	void TickState(float DeltaTime) override;
	void ExitState() override;
};
