// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseState.h"
UBaseState::UBaseState(){}
UBaseState::~UBaseState(){
	_character = nullptr;
	_stateController = nullptr;
}
UBaseState* UBaseState::Init(ADHPCharacter* character, UStateControllerComponent* stateController) { return this; }




void UBaseState::EnterState(){}
void UBaseState::TickState(float DeltaTime){}
void UBaseState::ExitState(){}
