// Fill out your copyright notice in the Description page of Project Settings.


#include "EQSFunctionLibrary.h"

#include "EnvironmentQuery/EnvQueryManager.h"

void UEQSFunctionLibrary::StopEQSQueryByQuerier(UObject* WorldContextObject, UObject* Querier)
{
	UEnvQueryManager* EQSManager = UEnvQueryManager::GetCurrent(WorldContextObject);

	EQSManager->RemoveAllQueriesByQuerier(*Querier, false);
}
