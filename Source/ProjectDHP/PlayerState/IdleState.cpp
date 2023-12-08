// Fill out your copyright notice in the Description page of Project Settings.

#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "../Player/DHPCharacter.h"

UIdleState::UIdleState(){};
UIdleState* UIdleState::Init(ADHPCharacter* character, UStateControllerComponent* stateController) {
	this->_character  = character;
	this->_stateController = stateController;
	return this;
}

void UIdleState::EnterState(){
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enter Idle state"));
	_character->movementComponent->MaxWalkSpeed = _stateController->IdleMaxSpeed;
	_character->movementComponent->MaxAcceleration = _stateController->IdleMaxAcceleration;
}

 void UIdleState::TickState(float DeltaTime){
	 if (!_character->GetLastMovementInputVector().IsZero()) {
		 _stateController->EnterInNewState(_stateController->walkState);
	 }
	 if (_character->bPressedRun) {
		 _stateController->EnterInNewState(_stateController->runState);
	 }
	 if (_character->JumpKeyHoldTime > 0) {
		 _stateController->EnterInNewState(_stateController->jumpState);
	 }
	 if (_character->movementComponent->bWantsToCrouch) {
		 _stateController->EnterInNewState(_stateController->crouchState);
	 }
 }

 void UIdleState::ExitState(){
	 GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Exit Idle state"));
 }






