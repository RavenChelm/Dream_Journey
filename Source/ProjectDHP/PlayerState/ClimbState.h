// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "ClimbState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDHP_API UClimbState : public UBaseState
{
	GENERATED_BODY()
public:
		FVector target;
		float LerpAlpha = 0;
public:
	UClimbState();
	UClimbState* Init(ADHPCharacter* character, UStateControllerComponent* stateController);
	void EnterState() override;
	void TickState(float DeltaTime) override;
	void ExitState() override;
};
