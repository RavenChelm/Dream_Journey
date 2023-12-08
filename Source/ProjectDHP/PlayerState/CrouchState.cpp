#include "CrouchState.h"
#include "../Player/DHPCharacter.h"

UCrouchState::UCrouchState() {}
UCrouchState* UCrouchState::Init(ADHPCharacter* character, UStateControllerComponent* stateController) {
	this->_character = character;
	this->_stateController = stateController;
	return this;
}

void UCrouchState::EnterState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enter Crouch state"));
	_character->movementComponent->MaxWalkSpeed = _stateController->CrouchMaxSpeed;
	_character->movementComponent->MaxAcceleration = _stateController->CrouchMaxAcceleration;
	_stateController->ChangeCapsula(false);
	StateOn = true;
}

void UCrouchState::TickState(float DeltaTime) {
	if (_character->bPressedJump ) _stateController->EnterInNewState(_stateController->jumpState);
	if (StateOn && !_character->movementComponent->bWantsToCrouch && !_stateController->CanStande()) StateOn = false;
	if ((!_character->movementComponent->bWantsToCrouch && _stateController->CanStande()) || (!StateOn && _stateController->CanStande())) _stateController->EnterInNewState(_stateController->idleState);
}

void UCrouchState::ExitState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Exit Crouch state"));
	_stateController->ChangeCapsula(true);
}
