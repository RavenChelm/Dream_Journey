// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerReturnToStablePos.generated.h"

UCLASS()
class PROJECTDHP_API ATriggerReturnToStablePos : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:	
	// Sets default values for this actor's properties
	ATriggerReturnToStablePos();
		
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// overlap end function
	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
