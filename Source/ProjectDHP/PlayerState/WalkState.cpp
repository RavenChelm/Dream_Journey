#include "WalkState.h"
#include "../Player/DHPCharacter.h"

UWalkState::UWalkState() {};
UWalkState* UWalkState::Init(ADHPCharacter* character, UStateControllerComponent* stateController) {
	this->_character = character;
	this->_stateController = stateController;
	return this;
}
void UWalkState::EnterState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enter walk state"));
	_character->movementComponent->MaxWalkSpeed = _stateController->WalkMaxSpeed;
	_character->movementComponent->MaxAcceleration = _stateController->WalkMaxAcceleration;
}
void UWalkState::TickState(float DeltaTime) {
	if (_character->GetLastMovementInputVector().IsZero()) {
		_stateController->EnterInNewState(_stateController->idleState);
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

void UWalkState::ExitState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Exit walk state"));
}






