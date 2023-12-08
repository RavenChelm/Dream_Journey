// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "WalkState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDHP_API UWalkState : public UBaseState
{
	GENERATED_BODY()
public:
	UWalkState();
	UWalkState* Init(ADHPCharacter* character, UStateControllerComponent* stateController);
	void EnterState() override;
	void TickState(float DeltaTime) override;
	void ExitState() override;
};
