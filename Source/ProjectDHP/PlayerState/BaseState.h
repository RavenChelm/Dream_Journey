// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.generated.h"
class ADHPCharacter;
class UStateControllerComponent;


UCLASS(Abstract)
class PROJECTDHP_API UBaseState : public UObject
{
	GENERATED_BODY()
protected:
	ADHPCharacter* _character;
	UStateControllerComponent* _stateController;
public:
	UBaseState();
	virtual ~UBaseState();
	virtual UBaseState* Init(ADHPCharacter* character, UStateControllerComponent* stateController);
	virtual void EnterState() ;
	virtual void TickState(float DeltaTime) ;
	virtual void ExitState() ;
};
