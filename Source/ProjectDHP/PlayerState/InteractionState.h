// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PlayerState/BaseState.h"
#include "InteractionState.generated.h"
//class InteractionObject;


UCLASS()
class PROJECTDHP_API UInteractionState : public UBaseState
{
	GENERATED_BODY()

public:
	//InteractionObject _interactObj;
public:
	UInteractionState();
	UInteractionState* Init(ADHPCharacter* character, UStateControllerComponent* stateController/*, InteractionObject interactObj*/);
	void EnterState() override;
	void TickState(float DeltaTime) override;
	void ExitState() override;
};
