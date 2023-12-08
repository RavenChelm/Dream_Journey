// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "InstanceGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDHP_API UInstanceGame : public UGameInstance
{
	GENERATED_BODY()
	
public:
	TMap<int, FString> ToolTip;
public: 
	bool ReedToolTipJson(int LocationKey);
};
