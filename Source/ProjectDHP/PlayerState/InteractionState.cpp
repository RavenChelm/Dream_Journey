// Fill out your copyright notice in the Description page of Project Settings.


#include "../PlayerState/InteractionState.h"
#include "InteractionState.h"
#include "../Player/DHPCharacter.h"

UInteractionState::UInteractionState() {}
UInteractionState* UInteractionState::Init(ADHPCharacter* character, UStateControllerComponent* stateController/*, InteractionObject interactObj*/) {
	this->_character = character;
	this->_stateController = stateController;
	//this->_interactObj = interactObj
	return this;
}

void UInteractionState::EnterState()
{
	_character->movementComponent->MaxWalkSpeed = 0;
}

void UInteractionState::TickState(float DeltaTime)
{

}

void UInteractionState::ExitState()
{
}
