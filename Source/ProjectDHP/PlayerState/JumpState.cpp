// Fill out your copyright notice in the Description page of Project Settings.
#include "JumpState.h"
#include "IdleState.h"
#include "../Player/DHPCharacter.h"
#include "DrawDebugHelpers.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

UJumpState::UJumpState(){}
UJumpState* UJumpState::Init(ADHPCharacter* character, UStateControllerComponent* stateController) {
	this->_character = character;
	this->_stateController = stateController;
	return this;
}
void UJumpState::EnterState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enter Jump state"));
	_character->movementComponent->MaxWalkSpeed = _stateController->JumpMaxSpeed;

	//if(_character->movementComponent->IsMovingOnGround())
	//{
	//	print("Save Last Position");
	//	_character->SaveLoadComponent->playerLastLocation = _character->GetActorLocation();
	//}
}

void UJumpState::TickState(float DeltaTime) {
	
	if (_character->movementComponent->IsMovingOnGround()){
		_stateController->prevWallDirection = UStateControllerComponent::WallDirection::None;
		_stateController->EnterInNewState(_stateController->idleState);

	}
	if (_stateController->CanClimb()) {
		_stateController->prevWallDirection = UStateControllerComponent::WallDirection::None;
		_stateController->EnterInNewState(_stateController->climbState);
	}
	if (_stateController->WallIsNear(_stateController->wallDirection, _stateController->HitLeftResult, _stateController->HitRightResult)
		&& _stateController->prevWallDirection != _stateController->wallDirection) { // Add Condition for Run, but not just jump;
		_stateController->prevWallDirection = _stateController->wallDirection;
		_stateController->EnterInNewState(_stateController->wallRunState);
	}
	if (_character->movementComponent->Velocity.Length() <= _stateController->thresholdVelosity && _character->movementComponent->bWantsToCrouch) {
		_stateController->prevWallDirection = UStateControllerComponent::WallDirection::None;
		_stateController->EnterInNewState(_stateController->crouchState);
	}
	if (_character->movementComponent->bWantsToCrouch) { //Maybe Change bWantsToChouch to another bool from _character 
		_stateController->prevWallDirection = UStateControllerComponent::WallDirection::None;
		_stateController->EnterInNewState(_stateController->slideState);

	}
}

void UJumpState::ExitState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Exit Jump state"));
}
