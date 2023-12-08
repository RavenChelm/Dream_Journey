#include "RunState.h"
#include "../Player/DHPCharacter.h"


URunState::URunState() {};
URunState* URunState::Init(ADHPCharacter* character, UStateControllerComponent* stateController) {
	this->_character = character;
	this->_stateController = stateController;
	return this;
}
void URunState::EnterState()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enter Run state"));
	_character->movementComponent->MaxWalkSpeed = _stateController->RunMaxSpeed;
	_character->movementComponent->MaxAcceleration = _stateController->RunMaxAcceleration;
}

void URunState::TickState(float DeltaTime)
{
	if (!_character->bPressedRun) {
		_stateController->EnterInNewState(_stateController->idleState);
	}
	if (_character->JumpKeyHoldTime > 0) {
		_stateController->EnterInNewState(_stateController->jumpState);
	}
	if (_character->movementComponent->bWantsToCrouch) { //Maybe Change bWantsToChouch to another bool from _character 
		_stateController->EnterInNewState(_stateController->slideState);
	}

}

void URunState::ExitState()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Exit Run state"));

}
