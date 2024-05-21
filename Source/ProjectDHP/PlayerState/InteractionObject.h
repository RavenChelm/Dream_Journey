#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionObject.generated.h"

class ADHPCharacter;

UCLASS()
class PROJECTDHP_API AInteractionObject : public AActor
{
    GENERATED_BODY()

public:
    // Конструктор
    AInteractionObject();

    // Методы для обработки взаимодействия
    void OnInteractionBegin(ADHPCharacter* character);
    void OnInteractionTick(float DeltaTime);
    void OnInteractionEnd(ADHPCharacter* character);
};