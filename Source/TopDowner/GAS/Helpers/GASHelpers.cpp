// Fill out your copyright notice in the Description page of Project Settings.


#include "GASHelpers.h"

#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"

float UGASHelpers::GetSnapshotedValue(const FGameplayEffectSpecHandle& Spec, FGameplayAttribute Attribute)
{
	FGameplayEffectAttributeCaptureDefinition Def;
	Def.bSnapshot = true;
	Def.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	Def.AttributeToCapture = Attribute;
	const auto Attr =  Spec.Data->CapturedRelevantAttributes.FindCaptureSpecByDefinition(Def, true);

	const FAggregatorEvaluateParameters EvalParams;
	float Magnitude;
	Attr->AttemptCalculateAttributeMagnitude(EvalParams, Magnitude);
	return Magnitude;
}
