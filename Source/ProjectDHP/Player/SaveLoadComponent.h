// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SaveLoadComponent.generated.h"
class ADHPCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTDHP_API USaveLoadComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USaveLoadComponent();
	bool LocalLoadPosition(ADHPCharacter* character);
public:
	FVector playerLastLocation;

		
};
