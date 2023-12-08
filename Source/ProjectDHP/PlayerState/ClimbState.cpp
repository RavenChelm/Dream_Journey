
#include "ClimbState.h"
#include "../Player/DHPCharacter.h"
#include "Kismet/GameplayStatics.h" 

UClimbState::UClimbState() {};
UClimbState* UClimbState::Init(ADHPCharacter* character, UStateControllerComponent* stateController) {
	this->_character = character;
	this->_stateController = stateController;
	return this;
}

void UClimbState::EnterState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enter Climb state"));
    _stateController->capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    _character->movementComponent->Velocity = FVector::ZeroVector;
    _character->ClimbTimelineComponent->PlayFromStart();
}

void UClimbState::TickState(float DeltaTime) {
    if (_stateController->MoveCharacter(target, DeltaTime)) {
        _stateController->EnterInNewState(_stateController->idleState);
    }
}

void UClimbState::ExitState() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Exit Climb state"));
    _stateController->capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}



/*
    // Параметры луча
    float SphereRadius = 100.f; 
    float SphereDistance = 100.f; 
    FVector TraceStart = _character->GetActorLocation(); 
    FVector TraceEnd = TraceStart + (_character->GetActorForwardVector() * _stateController->WallDistance); 
    ECollisionChannel CollisionChannel = ECC_Visibility; 
    TArray<FHitResult> OutHits;


    bool bHit = _character->GetWorld()->SweepMultiByChannel(OutHits, TraceStart, TraceEnd, FQuat::Identity, CollisionChannel, FCollisionShape::MakeSphere(SphereRadius));


    //Find Obj
    float distanceMin = TNumericLimits<float>::Max();;
    AActor* nearestAct = nullptr;
    if (bHit){
        for (const FHitResult& Hit : OutHits){
            AActor* HitActor = Hit.GetActor();
            if (HitActor)
            {
                // ВОЗМОЖЕН БАГ, НЕОБХОДИМО РАССТОЯНИЕ ДО БЛИЖАЙШЕЙ ТОЧКИ, А НЕ ДО ЦЕНТРА 
                // HitActor has Tag Climb Obj
                float distance = FVector::Distance(HitActor->GetActorLocation(), TraceStart);
                if (distance < distanceMin){
                    distanceMin = distance;
                    nearestAct = HitActor;
                }
            }
        }
    }

    //Find Surface
    FVector UpVector = _character->GetActorUpVector();
    float MinDotProduct = TNumericLimits<float>::Max();
    FPlane UppermostPlaneObj;
    FPlane* UppermostPlane = &UppermostPlaneObj;
    if (nearestAct != nullptr)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Object")));
        TArray<UStaticMeshComponent*> MeshComponents;
        nearestAct->GetComponents<UStaticMeshComponent>(MeshComponents);

        float UppermostPlaneZ = -1e10; // Начальное значение для поиска плоскости выше всех других

        for (auto MeshComponent : MeshComponents)
        {
            FTransform ComponentTransform = MeshComponent->GetComponentTransform();            // Получаем матрицу преобразования материала компонента Mesh
            FMatrix ComponentTransformMatrix = ComponentTransform.ToMatrixNoScale();
            FVector PlaneNormal = ComponentTransformMatrix.GetUnitAxis(EAxis::Z);            // Получаем нормаль плоскости из матрицы преобразования
            //????????????????????????????

            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Plane Normal: %s"), *PlaneNormal.ToString()));
            //WARNINIG MAGIC NUMBER
            //WARNINIG MAGIC NUMBER
            //WARNINIG MAGIC NUMBER

            float PlaneZ = ComponentTransformMatrix.GetOrigin().Z + (MeshComponent->K2_GetComponentLocation().Z * MeshComponent->GetComponentScale().Z)
                +_stateController->capsule->GetUnscaledCapsuleHalfHeight()*2+10;
            //PlaneNormal.Z > 0 &&
            if ( PlaneZ > UppermostPlaneZ)
            {
                UppermostPlaneZ = PlaneZ;
                *UppermostPlane = FPlane(PlaneNormal, PlaneZ);
            }
        }
    }

    //Find Point UppermostPlane
    FVector NearestPointOnPlane;
    if (UppermostPlane != nullptr) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Surface is finded ")));
        FVector planeNormal = UppermostPlane->GetSafeNormal();        // Получить нормаль плоскости
        FVector planePoint = UppermostPlane->GetOrigin();        // Получить точку на плоскости
        FVector vectorToPlane = planePoint - TraceStart; // Вычислить вектор от игрока до точки на плоскости
        FVector projectedVector = FVector::DotProduct(vectorToPlane, planeNormal) * planeNormal;        // Найти проекцию вектора на нормаль плоскости
        target = TraceStart + projectedVector;        // Найти ближайшую точку на плоскости к игроку

        //DEBUG LOG
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Object : %s"), *nearestAct->GetActorLocation().ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Player: %s"), *TraceStart.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Target: %s"), *target.ToString()));
    }

    _character->SetActorLocation(target);*/

