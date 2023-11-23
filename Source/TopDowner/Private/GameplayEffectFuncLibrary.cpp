// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEffectFuncLibrary.h"

void UGameplayEffectFuncLibrary::SetSourceObject(FGameplayEffectContextHandle EffectContext, UObject* NewSourceObject)
{
	EffectContext.AddSourceObject(NewSourceObject);
}
