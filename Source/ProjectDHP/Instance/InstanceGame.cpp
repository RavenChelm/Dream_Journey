// Fill out your copyright notice in the Description page of Project Settings.

#include "InstanceGame.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Json.h"

bool UInstanceGame::ReadToolTipJson(int LocationKey)
{
    // Имя файла JSON
    FString FileName = FPaths::ProjectContentDir() / TEXT("Data/ToolTips.json");

    // Проверяем, удалось ли загрузить данные из JSON
    if (!LoadJsonData(FileName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load JSON data."));
        return false;
    }

    // Проверяем, существует ли данный ключ в карте
    if (ToolTip.Contains(LocationKey))
    {
        FString ToolTipText = ToolTip[LocationKey];
        UE_LOG(LogTemp, Log, TEXT("ToolTip for LocationKey %d: %s"), LocationKey, *ToolTipText);
        return true;
    }

    // Если ключ не найден
    UE_LOG(LogTemp, Warning, TEXT("LocationKey %d not found in ToolTip map."), LocationKey);
    return false;
}

bool UInstanceGame::LoadJsonData(const FString& FileName)
{
    FString JsonString;
    if (!FFileHelper::LoadFileToString(JsonString, *FileName))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load file %s"), *FileName);
        return false;
    }

    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
    TSharedPtr<FJsonObject> JsonObject;
    if (!FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON file."));
        return false;
    }

    // Очищаем карту перед загрузкой новых данных
    ToolTip.Empty();

    // Заполняем карту ToolTip данными из JSON
    for (auto& Elem : JsonObject->Values)
    {
        int Key = FCString::Atoi(*Elem.Key);
        FString Value = Elem.Value->AsString();
        ToolTip.Add(Key, Value);
    }

    return true;
}