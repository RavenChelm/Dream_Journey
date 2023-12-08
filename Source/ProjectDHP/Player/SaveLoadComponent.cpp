// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadComponent.h"
#include "../Player/DHPCharacter.h"

USaveLoadComponent::USaveLoadComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

bool USaveLoadComponent::LocalLoadPosition(ADHPCharacter* character)
{
	if (!playerLastLocation.IsZero()) {
		character->SetActorLocation(playerLastLocation);
		return true;
	}
	character->SetActorLocation(FVector::Zero());
	return false;
}


