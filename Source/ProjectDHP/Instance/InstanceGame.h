
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
	// Функция для чтения JSON-файла и загрузки данных в карту ToolTip
	bool ReadToolTipJson(int LocationKey);

private:
	// Вспомогательная функция для загрузки данных из JSON-файла
	bool LoadJsonData(const FString& FileName);
};