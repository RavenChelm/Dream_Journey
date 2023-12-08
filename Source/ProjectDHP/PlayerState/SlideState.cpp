#include "SlideState.h"
#include "../Player/DHPCharacter.h"


USlideState::USlideState() {}
USlideState* USlideState::Init(ADHPCharacter* character, UStateControllerComponent* stateController) {
	this->_character = character;
	this->_stateController = stateController;
	return this;
}


void USlideState::EnterState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enter Slide state"));
	
	
	_character->movementComponent->MaxWalkSpeed = _stateController->SlideMaxSpeed;
	_character->movementComponent->MaxAcceleration = _stateController->SlideMaxAcceleration;
	_character->movementComponent->MaxAcceleration = _stateController->CrouchMaxAcceleration;
	_character->movementComponent->GroundFriction = _stateController->GroundFrictionSlide;
	_character->movementComponent->BrakingDecelerationWalking = _stateController->BrakingDecelerationSlide;



	_stateController->ChangeCapsula(false);
	_stateController->character->SlideTimelineComponent->Play();
	_stateController->character->CameraTimelineComponent->Play();

}


void USlideState::TickState(float DeltaTime) {
	//Inertia force
		FVector NewVelocity = _character->GetVelocity();
		NewVelocity -= NewVelocity * DeltaTime;
		_character->movementComponent->Velocity = NewVelocity;

	if (_character->bPressedJump ) {    //Не давать прыгнуть
		_stateController->EnterInNewState(_stateController->jumpState);
	}
	if (_character->movementComponent->Velocity.Length() <= _stateController->thresholdVelosity && _character->movementComponent->bWantsToCrouch) {
		_stateController->EnterInNewState(_stateController->crouchState);
	}
	if (_character->movementComponent->Velocity.Length() <= _stateController->thresholdVelosity && !_character->movementComponent->bWantsToCrouch ) {
		_stateController->EnterInNewState(_stateController->idleState);
	}
}

void USlideState::ExitState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Exit Slide state"));
	//_character->movementComponent->bOrientRotationToMovement = true;
	_stateController->ChangeCapsula(true);
	_stateController->character->SlideTimelineComponent->Stop();
	_stateController->character->CameraTimelineComponent->Reverse();
	_character->movementComponent->GroundFriction = _stateController->GroundFrictionGeneral;
	_character->movementComponent->BrakingDecelerationWalking = _stateController->BrakingDecelerationGeneral;

}






