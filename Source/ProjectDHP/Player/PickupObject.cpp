PickupObject.cpp
#include "PickupObject.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

APickupObject::APickupObject()
{
    PrimaryActorTick.bCanEverTick = true;

    // Создание коллайдера и установка в качестве корневого компонента
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;

    // Создание статической меш-структуры
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
}

void APickupObject::BeginPlay()
{
    Super::BeginPlay();
}

void APickupObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}