#include "../PlayerState/InteractionState.h"
#include "InteractionState.h"
#include "../Player/DHPCharacter.h"
#include "../Components/StateControllerComponent.h" // Не забудьте включить компоненты, которые вы используете

UInteractionState::UInteractionState() {}

UInteractionState* UInteractionState::Init(ADHPCharacter* character, UStateControllerComponent* stateController, AInteractionObject* interactObj) {
    this->_character = character;
    this->_stateController = stateController;
    this->_interactObj = interactObj; // Инициализация объекта взаимодействия
    return this;
}

void UInteractionState::EnterState()
{
    if (_character && _character->movementComponent)
    {
        _character->movementComponent->MaxWalkSpeed = 0;
    }

    if (_interactObj)
    {
        _interactObj->OnInteractionBegin(_character); // Вызов функции начала взаимодействия
    }
}

void UInteractionState::TickState(float DeltaTime)
{
    // Здесь можно добавить код для обработки состояния взаимодействия каждую тик
    if (_interactObj)
    {
        _interactObj->OnInteractionTick(DeltaTime); // Обновление взаимодействия каждый тик
    }
}

void UInteractionState::ExitState()
{
    if (_character && _character->movementComponent)
    {
        _character->movementComponent->MaxWalkSpeed = _character->DefaultWalkSpeed; // Возвращаем скорость
    }

    if (_interactObj)
    {
        _interactObj->OnInteractionEnd(_character); // Вызов функции завершения взаимодействия
    }
}