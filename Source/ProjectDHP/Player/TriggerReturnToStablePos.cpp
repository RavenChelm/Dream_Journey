// Fill out your copyright notice in the Description page of Project Settings.


#include "../Player/TriggerReturnToStablePos.h"
#include "TriggerReturnToStablePos.h"
#include "DrawDebugHelpers.h"
#include "../Player/SaveLoadComponent.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))


void ATriggerReturnToStablePos::BeginPlay()
{
    Super::BeginPlay();
    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

// Sets default values
ATriggerReturnToStablePos::ATriggerReturnToStablePos()
{
	PrimaryActorTick.bCanEverTick = true;

    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &ATriggerReturnToStablePos::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &ATriggerReturnToStablePos::OnOverlapEnd);

}	

void ATriggerReturnToStablePos::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    if (OtherActor && (OtherActor != this)) {
        // print to screen using above defined method when actor enters trigger box
        OtherActor->SetActorLocation(OtherActor->GetComponentByClass<USaveLoadComponent>()->playerLastLocation);
        print("Overlap Begin");
        printFString("Overlapped Actor = %s", *OverlappedActor->GetName());
    }
}

void ATriggerReturnToStablePos::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
    if (OtherActor && (OtherActor != this)) {
        // print to screen using above defined method when actor leaves trigger box
        print("Overlap Ended");
        printFString("%s has left the Trigger Box", *OtherActor->GetName());
    }
}


