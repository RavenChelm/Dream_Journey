#include "InteractionObject.h"
#include "../Player/DHPCharacter.h"

// Конструктор
AInteractionObject::AInteractionObject()
{
    PrimaryActorTick.bCanEverTick = true; // Если объект должен тикать
}

void AInteractionObject::OnInteractionBegin(ADHPCharacter* character)
{
    // Код для начала взаимодействия
    UE_LOG(LogTemp, Log, TEXT("Interaction started with %s"), *character->GetName());
    // Дополнительная логика взаимодействия, например, запуск анимации или звука
}

void AInteractionObject::OnInteractionTick(float DeltaTime)
{
    // Код для обработки взаимодействия каждую тик
    UE_LOG(LogTemp, Log, TEXT("Interaction ticking with DeltaTime: %f"), DeltaTime);
    // Дополнительная логика взаимодействия, например, обновление состояния объекта
}

void AInteractionObject::OnInteractionEnd(ADHPCharacter* character)
{
    // Код для завершения взаимодействия
    UE_LOG(LogTemp, Log, TEXT("Interaction ended with %s"), *character->GetName());
    // Дополнительная логика завершения взаимодействия, например, остановка анимации или звука
}