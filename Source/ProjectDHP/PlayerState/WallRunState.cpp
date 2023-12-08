
#include "WallRunState.h"
#include "../Player/DHPCharacter.h"

//THIS NEEDS REFACTORING
UWallRunState::UWallRunState() {}
UWallRunState* UWallRunState::Init(ADHPCharacter* character, UStateControllerComponent* stateController) {
	this->_character = character;
	this->_stateController = stateController;
	return this;
}
void UWallRunState::EnterState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enter WallRun state"));

	//Out to BluePrint
	_character->movementComponent->AirControl = 0.7f;
	_character->movementComponent->GravityScale = 0.2f;
	_character->JumpCurrentCount = 0;
	_character->JumpMaxCount = 2;
	_character->JumpKeyHoldTime = 0;
	_stateController->character->CameraTimelineComponent->Play();
	_stateController->CurrentTimeRun = 0;

}

void UWallRunState::TickState(float DeltaTime) {
	if (_character->movementComponent->IsMovingOnGround()) {
		_stateController->prevWallDirection = UStateControllerComponent::WallDirection::None;
		_stateController->EnterInNewState(_stateController->idleState);
	}
	bool wallNear = _stateController->WallIsNear(_stateController->wallDirection, _stateController->HitLeftResult, _stateController->HitRightResult);
	FVector ImpactPoint = _stateController->wallDirection == UStateControllerComponent::WallDirection::Right ?
		_stateController->HitLeftResult->ImpactPoint : _stateController->HitRightResult->ImpactPoint;

	if (_stateController->CurrentTimeRun <= _stateController->MaxTimeRun && 
		( wallNear || FVector::Distance(_character->GetActorLocation(), ImpactPoint) <= 40.f)) {

		_stateController->CurrentTimeRun += DeltaTime;

		float cosForceUp = UKismetMathLibrary::Cos(_stateController->CurrentTimeRun / _stateController->MaxTimeRun * UKismetMathLibrary::GetPI());
		_character->movementComponent->AddForce(_character->GetActorUpVector() * _stateController->FVup * 
			(cosForceUp < 0.f ? cosForceUp * 100 : cosForceUp ) );
		
		float sinForceFwrd = UKismetMathLibrary::Sin((_stateController->MaxTimeRun - _stateController->CurrentTimeRun) / _stateController->MaxTimeRun * UKismetMathLibrary::GetPI());
		_character->movementComponent->AddForce(_character->GetActorForwardVector() * _stateController->FVforward * 
			(sinForceFwrd < 0.5f ? sinForceFwrd * 0.01 : sinForceFwrd) );


		FVector velosity = (_character->movementComponent->GetLastUpdateVelocity());
		_character->movementComponent->Velocity = FVector(velosity.X, velosity.Y, velosity.Z - DeltaTime * 100);

	}
	else {
		_stateController->EnterInNewState(_stateController->jumpState);
	}

	if (_character->JumpKeyHoldTime > 0) {

		FVector directionJump = (-1) * (_stateController->wallDirection == UStateControllerComponent::WallDirection::Right ?
			_stateController->HitRightResult->Normal - _stateController->HitRightResult->ImpactPoint :
			_stateController->HitLeftResult->Normal - _stateController->HitLeftResult->ImpactPoint);
		directionJump.Normalize();

		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green,
		FString::SanitizeFloat(directionJump.X) +
		FString::FString(" ") + FString::SanitizeFloat(directionJump.Y) +
		FString::FString(" ") + FString::SanitizeFloat(directionJump.Z));

		FVector Force = (
			//right/left
			(_stateController->wallDirection == UStateControllerComponent::WallDirection::Right ?
				(-1) * _character->GetActorRightVector() : _character->GetActorRightVector()) * _stateController->JumpFromWallSpeed_XY) +
			//Up
			 (_character->GetActorUpVector() * _stateController->JumpFromWallSpeed_Z) +
			//forward
			(_character->GetActorForwardVector() * _stateController->JumpFromWallSpeed_XY);

		_character->LaunchCharacter ( Force, true, false);
		_stateController->EnterInNewState(_stateController->jumpState);

	}

}

void UWallRunState::ExitState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Exit WallRun state"));
	_character->movementComponent->AirControl = _stateController->AirConroll;
	_character->movementComponent->GravityScale = _stateController->GravityScale;
	_character->JumpMaxCount = 1;
	_stateController->character->CameraTimelineComponent->Reverse();


}






